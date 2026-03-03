#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <filesystem>
#include <map>
#include <string>

#if defined(_WIN32)
	#include <windows.h>
#elif defined(__linux__)
	#include <unistd.h>
	#include <limits.h>
#elif defined(__APPLE__)
	#include <mach-o/dyld.h>
#endif


#include <caffeine-gl/gfx/Shader.hpp>
#include <caffeine-gl/gfx/Texture.hpp>

#include <caffeine-gl/game/CaffeineGameObject.hpp>

class ResourceManager {
public:
	static std::filesystem::path getExecutablePath();
	static void setResourceRoot(const std::filesystem::path& root);
	static std::filesystem::path getResourceRoot();


	static Shader loadShader(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath, const std::string &name);
	static Shader& getShader(const std::string& name);

	static Texture loadTexture(const char *file, bool alpha, const std::string& name);
	static Texture& getTexture(const std::string &name);


	static void clear();

private:
	static std::filesystem::path resourceRoot;
	static std::filesystem::path resolveResourcePath(const std::filesystem::path& relativePath);


	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;
	static std::vector<CaffeineGameObject*> gameObjects;


	static Shader createShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath = nullptr);
	static std::string loadShaderCodeFromFile(const std::filesystem::path& path);
	static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif //RESOURCEMANAGER_H
