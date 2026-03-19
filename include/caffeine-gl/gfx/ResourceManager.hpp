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


#include <caffeine-gl/gfx/CaffeineShader.hpp>
#include <caffeine-gl/gfx/CaffeineTexture.hpp>

#include <caffeine-gl/game/CaffeineGameObject.hpp>

#include <caffeine-gl/gfx/CaffeineMesh.hpp>
//#include "caffeine-gl/game/CaffeineMeshDrawable.hpp"


class ResourceManager {
public:
	static std::filesystem::path getExecutablePath();
	static void setResourceRoot(const std::filesystem::path& root);
	static std::filesystem::path getResourceRoot();

	// Factory function to create game objects of any subclass type, ensuring they are properly stored and managed by the ResourceManager
	template<typename GameObjectSubclass, typename... Args>
	static GameObjectSubclass* createGameObject(int layer, Args &&... args) {
		static_assert(std::is_base_of_v<CaffeineGameObject, GameObjectSubclass>, "Subclass must derive from CaffeineGameObject");

		auto object = std::make_unique<GameObjectSubclass>(std::forward<Args>(args)...);

		GameObjectSubclass* ptr = object.get();
		gameObjects.push_back(std::move(object));

		if constexpr (std::is_base_of_v<CaffeineDrawable, GameObjectSubclass>) {
			drawableLayers[layer].push_back(static_cast<CaffeineDrawable*>(ptr));
		}

		return ptr;
	}

	static void renderAllDrawables();
	static void clear();


	static CaffeineShader& loadShader(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath, const std::string &name);
	static CaffeineShader& getShader(const std::string& name);

	static CaffeineTexture& loadTexture(const char *file, const std::string& name);
	static CaffeineTexture& getTexture(const std::string &name);

	static void createDefaultMeshes();
	static CaffeineMesh& loadMesh(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices, const std::string& name);
	static CaffeineMesh& getMesh(const std::string &name);

private:
	static std::filesystem::path resourceRoot;
	static std::filesystem::path resolveResourcePath(const std::filesystem::path& relativePath);

	static std::vector<std::unique_ptr<CaffeineGameObject>> gameObjects;
	static std::map<int, std::vector<CaffeineDrawable*>> drawableLayers;

	static std::map<std::string, CaffeineShader> shaders;
	static std::map<std::string, CaffeineTexture> textures;
	static std::map<std::string, CaffeineMesh> meshes;

	static CaffeineShader createShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath = nullptr);
	static std::string loadShaderCodeFromFile(const std::filesystem::path& path);
	static CaffeineTexture loadTextureFromFile(const char *path);
};

#endif //RESOURCEMANAGER_H
