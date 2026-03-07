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

#include "Mesh.hpp"
#include "caffeine-gl/game/CaffeineMeshDrawable.hpp"


class ResourceManager {
public:
	static std::filesystem::path getExecutablePath();
	static void setResourceRoot(const std::filesystem::path& root);
	static std::filesystem::path getResourceRoot();

	// Factory function to create game objects of any subclass type, ensuring they are properly stored and managed by the ResourceManager
	template<typename GameObjectSubclass, typename... Args>
	static GameObjectSubclass* createGameObject(Args &&... args) {
		static_assert(std::is_base_of_v<CaffeineGameObject, GameObjectSubclass>, "Subclass must derive from CaffeineGameObject");

		auto object = std::make_unique<GameObjectSubclass>(std::forward<Args>(args)...);

		GameObjectSubclass* ptr = object.get();
		gameObjects.push_back(std::move(object));

		if constexpr (std::is_base_of_v<CaffeineDrawable, GameObjectSubclass>)
		{
			drawables.push_back(static_cast<CaffeineDrawable*>(ptr));
		}

		return ptr;
	}

	static void renderAllDrawables(Renderer &renderer);
	static void clear();


	static Shader& loadShader(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath, const std::string &name);
	static Shader& getShader(const std::string& name);

	static Texture& loadTexture(const char *file, const std::string& name);
	static Texture& getTexture(const std::string &name);

	static void createDefaultMeshes();
	static Mesh& loadMesh(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices, const std::string& name);
	static Mesh& getMesh(const std::string &name);

private:
	static std::filesystem::path resourceRoot;
	static std::filesystem::path resolveResourcePath(const std::filesystem::path& relativePath);

	static std::vector<std::unique_ptr<CaffeineGameObject>> gameObjects;
	static std::vector<CaffeineDrawable*> drawables;

	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;
	static std::map<std::string, Mesh> meshes;

	static Shader createShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath = nullptr);
	static std::string loadShaderCodeFromFile(const std::filesystem::path& path);
	static Texture loadTextureFromFile(const char *path);
};

#endif //RESOURCEMANAGER_H
