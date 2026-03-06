#ifndef RENDERER_H
#define RENDERER_H

#include <caffeine-gl/gfx/Shader.hpp>
#include <caffeine-gl/gfx/Texture.hpp>

#include <caffeine-gl/gfx/Material.hpp>
#include <caffeine-gl/gfx/Mesh.hpp>

#include "caffeine-gl/game/Transform.hpp"

struct RenderingCommand {
	const Mesh& mesh;
	const Material& material;
	const Transform& transform;
};

class Renderer {
public:
	std::vector<RenderingCommand> renderingCommands;
	glm::mat4 projectionMatrix{};

	Renderer(float width, float height);

	void queueRenderingCommand(const Mesh &mesh, const Material &material, const Transform &transform);
	void renderAll();
};

#endif //RENDERER_H