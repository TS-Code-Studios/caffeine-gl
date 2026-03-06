#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

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
	static std::vector<RenderingCommand> renderingCommands;

	void queueRenderingCommand(const Mesh &mesh, const Material &material, const Transform &transform);
	void renderAll();
};

#endif //SPRITE_RENDERER_H