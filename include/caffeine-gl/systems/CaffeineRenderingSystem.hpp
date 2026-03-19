#ifndef RENDERER_H
#define RENDERER_H

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
	glm::mat4 projectionMatrix = glm::ortho(0.0f, virtualWidth, 0.0f, virtualHeight, -1.0f, 1.0f);;

	void update(CaffeineWorld& world);

private:
	std::vector<RenderingCommand> renderingCommands;

	void flush();
};

#endif //RENDERER_H