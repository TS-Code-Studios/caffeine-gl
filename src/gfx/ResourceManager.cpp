#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vertexShaderFile, const char *fragmentShaderFile, const char *geometryShaderFile, const std::string &name) {
    Shaders[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string& name) {
    return Shaders[name];
}


Texture ResourceManager::LoadTexture(const char *file, bool alpha, const std::string& name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture &ResourceManager::GetTexture(const std::string &name) {
    return Textures[name];
}


void ResourceManager::Clear() {
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }

    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second.ID);
    }
}


Shader ResourceManager::loadShaderFromFile(const char *vertexShaderInput, const char *fragmentShaderInput, const char *geometryShaderInput) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        // open files
        std::ifstream vertexShaderFile(vertexShaderInput);
        std::ifstream fragmentShaderFile(fragmentShaderInput);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        // read file's buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream into string
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();

        // Do the same for geometry shader if present
        if (geometryShaderInput != nullptr) {
            std::ifstream geometryShaderFile(geometryShaderInput);
            std::stringstream geometryShaderStream;
            geometryShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = geometryShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();
    const char *geometryShaderCode = geometryCode.c_str();

    Shader shader;
    shader.compile(vertexShaderCode, fragmentShaderCode, geometryShaderInput != nullptr ? geometryShaderCode : nullptr);
    return shader;
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