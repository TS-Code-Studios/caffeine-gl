#include <iostream>
#include <sstream>
#include <fstream>

#include <caffeine-gl/gfx/ResourceManager.hpp>
#include <caffeine-gl/gfx/stb_image.h>

std::filesystem::path ResourceManager::resourceRoot;

std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
std::vector<CaffeineGameObject*> ResourceManager::gameObjects;

// Free all loaded resources
void ResourceManager::clear() {
    for (const auto&[fst, snd] : shaders) {
        glDeleteProgram(snd.ID);
    }

    for (const auto&[fst, snd] : textures) {
        glDeleteTextures(1, &snd.ID);
    }

    for (const auto iteration : gameObjects) {
        delete iteration;
    }
}


// Resource path management functions

// Retrieves the executable's absolute path
// Experimental! To do: Check on all platforms
std::filesystem::path ResourceManager::getExecutablePath() {
    #if defined(_WIN32)
        char buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();

    #elif defined(__linux__)
        char result[PATH_MAX];
        const ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count == -1)
            throw std::runtime_error("Failed to read /proc/self/exe");
        return std::filesystem::path(std::string(result, count)).parent_path();

    #elif defined(__APPLE__)
        uint32_t size = 0;
        _NSGetExecutablePath(nullptr, &size);
        std::string buffer(size, '\0');
        if (_NSGetExecutablePath(buffer.data(), &size) != 0)
            throw std::runtime_error("Failed to get executable path");
        return std::filesystem::path(buffer).parent_path();

    #else
        #error Unsupported platform

    #endif
}

void ResourceManager::setResourceRoot(const std::filesystem::path& root) {
    resourceRoot = root;
}

std::filesystem::path ResourceManager::getResourceRoot() {
    if (resourceRoot.empty()) {
        throw std::runtime_error("Resource root not set. Call ResourceManager::setResourceRoot() before accessing resources.");
    }
    std::cout << resourceRoot << std::endl;
    return resourceRoot;
}

// Resolves a relative resource path to an absolute path based on the resource root
std::filesystem::path ResourceManager::resolveResourcePath(const std::filesystem::path &relativePath) {
    return getResourceRoot() / relativePath;
}


// Shader management functions
Shader ResourceManager::loadShader(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath, const std::string &name) {
    shaders[name] = createShaderProgram(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
    return shaders[name];
}

Shader& ResourceManager::getShader(const std::string& name) {
    return shaders[name];
}

// Texture management functions

Texture ResourceManager::loadTexture(const char *file, bool alpha, const std::string& name) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture &ResourceManager::getTexture(const std::string &name) {
    return textures[name];
}


// Internal functions for loading shader code and texture data from files

Shader ResourceManager::createShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath) {
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::string geometryShaderCode;


    try {
        const std::filesystem::path resolvedVertexPath = resolveResourcePath(vertexShaderPath).string();
        const std::filesystem::path resolvedFragmentPath = resolveResourcePath(fragmentShaderPath).string();

        vertexShaderCode = loadShaderCodeFromFile(resolvedVertexPath);
        fragmentShaderCode = loadShaderCodeFromFile(resolvedFragmentPath);

        // Only load geometry shader if a path is provided
        if (geometryShaderPath != nullptr) {
            const std::filesystem::path resolvedGeometryPath = resolveResourcePath(geometryShaderPath).string();

            geometryShaderCode = loadShaderCodeFromFile(resolvedGeometryPath);
        }
    }
    catch (const std::exception &e) {
        std::cerr << "ERROR::SHADER: Failed to read shader files" << std::endl;
        throw;
    }

    Shader shader;

    // Only pass geometry shader code if a path was provided
    shader.compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str(), geometryShaderPath != nullptr ? geometryShaderCode.c_str() : nullptr);

    return shader;
}

std::string ResourceManager::loadShaderCodeFromFile(const std::filesystem::path& path) {
    // Open file
    std::ifstream shaderFile(path);
    std::stringstream shaderStream;

    // Read file buffer content into stream
    shaderStream << shaderFile.rdbuf();
    // Close file handler
    shaderFile.close();

    // Convert stream into string, then into const char*, and return
    return shaderStream.str();
}


Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
    Texture texture;
    if (alpha) {
        texture.format_INTERNAL = GL_RGBA;
        texture.format_IMAGE = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if(data == nullptr) {
        file = "resources/textures/missing_texture.png";
        texture.format_INTERNAL = GL_RGB;
        texture.format_IMAGE = GL_RGB;

        data = stbi_load(file, &width, &height, &nrChannels, 0);
    }

    texture.filter_MAX = GL_NEAREST;

    texture.generate(width, height, data);


    stbi_image_free(data);
    return texture;
}