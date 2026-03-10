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
	static const float virtualWidth;
	static const float virtualHeight;

	static std::vector<RenderingCommand> renderingCommands;
	static glm::mat4 projectionMatrix;

	static void queueRenderingCommand(const Mesh &mesh, const Material &material, const Transform &transform);
	static void renderAll();
};

#endif //RENDERER_H