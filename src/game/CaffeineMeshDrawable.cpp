#include <iostream>
#include <caffeine-gl/game/CaffeineMeshDrawable.hpp>

CaffeineMeshDrawable::CaffeineMeshDrawable(const Mesh &mesh, const Material &material) {
	this->mesh = &mesh;
	this->material = material;
	Transform transform{};
}

void CaffeineMeshDrawable::submitToRenderer(Renderer &renderer) {
	renderer.queueRenderingCommand(*mesh, material, this->transform);
}

void CaffeineMeshDrawable::move(const glm::vec2 &delta) {
	transform.move(delta);
}

void CaffeineMeshDrawable::scale(const glm::vec2 &factor) {
	transform.scale(factor);
}

void CaffeineMeshDrawable::rotate(const float &radians) {
	transform.rotate(radians);
}

