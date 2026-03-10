#include <iostream>
#include <caffeine-gl/game/CaffeineMeshDrawable.hpp>

CaffeineMeshDrawable::CaffeineMeshDrawable(const Mesh &mesh, const Material &material)
	: mesh(&mesh), material(material), transform() {}

void CaffeineMeshDrawable::submitToRenderer() {
	Renderer::queueRenderingCommand(*mesh, material, this->transform);
}

void CaffeineMeshDrawable::setLocation(const glm::vec2 &position) {
	transform.position = position;
}
void CaffeineMeshDrawable::setSize(const glm::vec2 &scale) {
	transform.size = scale;
}
void CaffeineMeshDrawable::setRotation(const float &degrees) {
	transform.rotation = degrees;
}


void CaffeineMeshDrawable::translate(const glm::vec2 &delta) {
	transform.position += delta;
}
void CaffeineMeshDrawable::scale(const glm::vec2 &factor) {
	transform.size *= factor;
}
void CaffeineMeshDrawable::rotate(const float &degrees) {
	transform.rotation += degrees;
}