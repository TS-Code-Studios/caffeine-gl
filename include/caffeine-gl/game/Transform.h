#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
public:
	explicit Transform(const glm::vec2& position = {0.0f, 0.0f}, const float& rotation = 0.0f, const glm::vec2& scale = {1.0f, 1.0f})
			: position(position), scale(scale), rotation(rotation) {};

	glm::vec2 position, scale;
	float rotation;
};

#endif //TRANSFORM_H
