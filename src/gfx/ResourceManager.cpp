#include <iostream>
#include <sstream>
#include <fstream>

#include <caffeine-gl/gfx/ResourceManager.hpp>
#include <caffeine-gl/gfx/stb_image.h>

std::filesystem::path ResourceManager::resourceRoot;

std::vector<std::unique_ptr<CaffeineGameObject>> ResourceManager::gameObjects;
std::map<int, std::vector<CaffeineDrawable*>> ResourceManager::drawableLayers;

std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Mesh> ResourceManager::meshes;

void ResourceManager::renderAllDrawables() {
    for(auto& [layer, drawableArray] : drawableLayers) {
        for (CaffeineDrawable* drawable : drawableArray) {
            if(drawable->visible) {
                drawable->submitToRenderer();
            }
        }
    }
    Renderer::renderAll();
}

// Free all loaded resources
void ResourceManager::clear() {
    gameObjects.clear();

    for(auto& [layer, drawableArray] : drawableLayers) {
        for(const CaffeineDrawable* drawable : drawableArray) {
            delete drawable;
        }
    }
    drawableLayers.clear();

    shaders.clear();
    textures.clear();
    meshes.clear();
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
    return resourceRoot;
}

// Resolves a relative resource path to an absolute path based on the resource root
std::filesystem::path ResourceManager::resolveResourcePath(const std::filesystem::path &relativePath) {
    return getResourceRoot() / relativePath;
}


// Shader management functions
Shader& ResourceManager::loadShader(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath, const std::string &name) {
    shaders.emplace(name, createShaderProgram(vertexShaderPath, fragmentShaderPath, geometryShaderPath));
    return shaders.at(name);
}
Shader& ResourceManager::getShader(const std::string& name) {
    return shaders.at(name);
}

// Texture management functions
Texture& ResourceManager::loadTexture(const char *file, const std::string& name) {
    textures.emplace(name, loadTextureFromFile(file));
    return textures.at(name);
}
Texture& ResourceManager::getTexture(const std::string &name) {
    return textures.at(name);
}

// Mesh management functions
void ResourceManager::createDefaultMeshes() {
    const std::vector<Vertex2D> quadVertices = {
        {-0.5f, -0.5f, 0,0, 1,1,1,1}, // Bottom left
        { 0.5f, -0.5f, 1,0, 1,1,1,1}, // Bottom right
        {-0.5f,  0.5f, 0,1, 1,1,1,1}, // Top left
        { 0.5f,  0.5f, 1,1, 1,1,1,1}	// Top right
    };
    const std::vector<uint32_t> quadIndices = {0,1,2, 2,3,1};

    loadMesh(quadVertices, quadIndices, "quad");
}
Mesh& ResourceManager::loadMesh(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices, const std::string &name) {
    meshes.try_emplace(name, vertices, indices);
    return meshes.at(name);
}
Mesh& ResourceManager::getMesh(const std::string &name) {
    return meshes.at(name);
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


Texture ResourceManager::loadTextureFromFile(const char *path) {
    std::string resolvedPath = resolveResourcePath(path).string();

    Texture texture;

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(resolvedPath.c_str(), &width, &height, &nrChannels, 0);


    if(data == nullptr) {
        std::cerr << "Failed to load texture: " << resolvedPath << ", falling back to placeholder" << std::endl;

        resolvedPath = resolveResourcePath("textures/missing_texture.png").string();
        texture.format_INTERNAL = GL_RGB;
        texture.format_IMAGE = GL_RGB;

        data = stbi_load(resolvedPath.c_str(), &width, &height, &nrChannels, 0);
    }

    texture.filter_MAX = GL_NEAREST;
    if(nrChannels == 4) {
        texture.format_IMAGE = GL_RGBA;
        texture.format_INTERNAL = GL_RGBA;
    } else if(nrChannels == 3) {
        texture.format_IMAGE = GL_RGB;
        texture.format_INTERNAL = GL_RGB;
    }

    texture.generate(width, height, data);


    stbi_image_free(data);
    return texture;
}