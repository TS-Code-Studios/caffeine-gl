#ifndef CAFFEINERENDERINGSYSTEM_H
#define CAFFEINERENDERINGSYSTEM_H

#include <caffeine-gl/game/CaffeineWorld.hpp>

#include <caffeine-gl/components/CaffeineMeshComponent.hpp>
#include <caffeine-gl/components/CaffeineMaterialComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

struct RenderingCommand {
	int layer;

	const CaffeineMesh* mesh;
	const CaffeineMaterialComponent* material;
	const CaffeineTransformComponent* transform;
};

class CaffeineRenderingSystem {
public:
	static constexpr float virtualWidth = 1920.0f;
	static constexpr float virtualHeight = 1080.0f;
	static glm::mat4 projectionMatrix;

	static void update(CaffeineWorld& world);

private:
	static std::vector<RenderingCommand> renderingCommands;

	static void flush();
};

#endif //CAFFEINERENDERINGSYSTEM_H