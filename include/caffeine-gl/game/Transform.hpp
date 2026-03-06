#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
public:
	glm::vec2 position{};
	float rotation;
	glm::vec2 size{};

	explicit Transform(glm::vec2 position = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 size = glm::vec2(1.0f));

	[[nodiscard]] glm::mat4 getModelMatrix() const;
	void translate(const glm::vec2 &delta);
	void rotate(const float &radians);
	void scale(const glm::vec2 &factor);
};



#endif //TRANSFORM_HPP
