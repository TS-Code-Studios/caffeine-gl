#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>

struct AABB {
	glm::vec2 min;
	glm::vec2 max;
};

enum class ColliderType {
	QUAD,
	CIRCLE
};

// Can't include CaffeineGameObject.hpp here since it would be a circular dependency
class CaffeineGameObject;

class Collider {
public:
	ColliderType type;

	bool enabled = false;

	glm::vec2 offset{};
	glm::vec2 size{};

	CaffeineGameObject* parent;

	//Collider() = default;
	Collider(CaffeineGameObject* parent, ColliderType type, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f));

	[[nodiscard]] AABB getWorldSpaceAABB() const;

	void enable();
	void disable();
};

#endif //COLLIDER_HPP
