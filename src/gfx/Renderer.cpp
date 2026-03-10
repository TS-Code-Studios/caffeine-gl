#include <iostream>
#include <caffeine-gl/gfx/Renderer.hpp>

std::vector<RenderingCommand> Renderer::renderingCommands;

const float Renderer::virtualWidth = 1920.0f;
const float Renderer::virtualHeight = 1080.0f;
glm::mat4 Renderer::projectionMatrix = glm::ortho(0.0f, virtualWidth, 0.0f, virtualHeight, -1.0f, 1.0f);

void Renderer::queueRenderingCommand(const Mesh &mesh, const Material &material, const Transform &transform) {
	renderingCommands.push_back({ mesh, material, transform});
}

void Renderer::renderAll() {
	for(auto &[mesh, material, transform] : renderingCommands) {

		material.shader->activate();

		material.shader->setMatrix4("projectionMatrix", projectionMatrix, true);

		material.shader->setMatrix4("modelMatrix", transform.getModelMatrix(), true);

		if(material.texture) {
			glActiveTexture(GL_TEXTURE0);
			material.shader->setInteger("image", 0);
			material.texture->bind();
		}

		mesh.draw();
	}

	renderingCommands.clear();
}
