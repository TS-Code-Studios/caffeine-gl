#include <caffeine-gl/game/Transform.hpp>

Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale) {
	this->position = position;
	this->rotation = rotation;
	this->size = scale;
}

void Transform::translate(const glm::vec2 &delta) {
	position += delta;
}

void Transform::rotate(const float &degrees) {
	this->rotation += degrees;
}


void Transform::scale(const glm::vec2 &factor) {
	this->size *= factor;
}


glm::mat4 Transform::getModelMatrix() const {
	auto modelMatrix = glm::mat4(1.0f);

	// Apply transformations in the order: scale, rotate, translate
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));

	return modelMatrix;
}