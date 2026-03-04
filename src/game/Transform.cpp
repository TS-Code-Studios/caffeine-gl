#include <caffeine-gl/game/Transform.hpp>

Transform::Transform(glm::vec3 position, float rotation, glm::vec2 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}