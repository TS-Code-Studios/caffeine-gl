#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

CaffeineTransformComponent::CaffeineTransformComponent(const glm::vec2 position, const float rotation, const glm::vec2 size) {
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}


glm::mat4 CaffeineTransformComponent::getModelMatrix() const {
	auto modelMatrix = glm::mat4(1.0f);

	// Apply transformations in the order: scale, rotate, translate
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

	return modelMatrix;
}