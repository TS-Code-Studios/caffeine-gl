#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <caffeine-gl/gfx/Shader.hpp>
#include <caffeine-gl/gfx/Texture.hpp>

#include "Material.hpp"
#include "Mesh.hpp"

class Renderer {
public:
	

	explicit Renderer(Shader &shader);
	~Renderer();

	static void queueRenderingCommand(const Mesh &mesh, const Material &material);

private:
	Shader shader;
	unsigned int quadVAO;

	void initRenderData();
};

#endif //SPRITE_RENDERER_H