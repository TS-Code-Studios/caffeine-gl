#include <iostream>
#include <caffeine-gl/gfx/Renderer.hpp>

std::vector<RenderingCommand> Renderer::renderingCommands;

void Renderer::queueRenderingCommand(const Mesh &mesh, const Material &material, const Transform &transform) {
	renderingCommands.push_back({ mesh, material, transform});
	std::cout << "Queued rendering command with position (" << transform.position.x << ", " << transform.position.y << ")\n";
	std::cout << "Queued rendering command with size (" << transform.size.x << ", " << transform.size.y << ")\n";

}

void Renderer::renderAll() {
	for(auto &[mesh, material, transform] : renderingCommands) {

		if(material.texture) {
			material.texture->bind();
		}

		material.shader->setMatrix4("modelMatrix", transform.getModelMatrix());
		material.shader->activate();

		mesh.draw();
	}

	renderingCommands.clear();
}
