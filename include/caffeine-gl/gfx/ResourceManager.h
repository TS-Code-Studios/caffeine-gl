#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"

class ResourceManager {
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	static Shader LoadShader(const char *vertexShaderFile, const char *fragmentShaderFile, const char *geometryShaderFile, const std::string &name);
	static Shader& GetShader(const std::string& name);

	static Texture LoadTexture(const char *file, bool alpha, const std::string& name);
	static Texture &GetTexture(const std::string &name);

	static void Clear();
private:
	ResourceManager() = default;

	static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

	static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif //RESOURCEMANAGER_H
