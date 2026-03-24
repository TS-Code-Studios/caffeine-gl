#ifndef CAFFEINETRANSFORMCOMPONENT_HPP
#define CAFFEINETRANSFORMCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CaffeineTransformComponent : CaffeineComponent {
	glm::vec2 position = glm::vec2(0.0f);
	float rotation = 0.0f;
	glm::vec2 size = glm::vec2(1.0f);

	CaffeineTransformComponent(glm::vec2 position, float rotation, glm::vec2 size): position(position), rotation(rotation), size(size){};

	[[nodiscard]] glm::mat4 getModelMatrix() const {
		auto modelMatrix = glm::mat4(1.0f);

		// Apply transformations in the order: scale, rotate, translate
		modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

		return modelMatrix;
	};
};



#endif //CAFFEINETRANSFORMCOMPONENT_HPP
