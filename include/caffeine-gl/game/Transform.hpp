#ifndef CAFFEINETRANSFORM_HPP
#define CAFFEINETRANSFORM_HPP

#include <glm/glm.hpp>

class Transform {
public:
	glm::vec3 position{};
	float rotation;
	glm::vec2 scale{};

	explicit Transform(glm::vec3 position = glm::vec3(0.0f), float rotation = 0.0f, glm::vec2 scale = glm::vec2(1.0f));
};

#endif //CAFFEINETRANSFORM_HPP
