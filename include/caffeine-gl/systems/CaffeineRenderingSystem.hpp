#ifndef RENDERER_H
#define RENDERER_H

#include <caffeine-gl/game/CaffeineWorld.hpp>

#include <caffeine-gl/components/CaffeineMeshComponent.hpp>
#include <caffeine-gl/components/CaffeineMaterialComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

struct RenderingCommand {
	const CaffeineMesh* mesh;
	const CaffeineMaterial* material;
	const CaffeineTransformComponent& transform;
};

class CaffeineRenderingSystem {
public:
	const float virtualWidth = 1920.0f;
	const float virtualHeight = 1080.0f;
	glm::mat4 projectionMatrix = glm::ortho(0.0f, virtualWidth, 0.0f, virtualHeight, -1.0f, 1.0f);;

	void update(CaffeineWorld& world);

private:
	std::vector<RenderingCommand> renderingCommands;

	void flush();
};

#endif //RENDERER_H