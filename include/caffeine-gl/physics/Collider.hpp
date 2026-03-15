#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>

#include "caffeine-gl/game/CaffeineGameObject.hpp"

struct AABB {
	glm::vec2 min;
	glm::vec2 max;
};

enum class ColliderType {
	QUAD,
	CIRCLE
};

class Collider {
public:
	ColliderType type;

	bool enabled = true;

	glm::vec2 offset;
	glm::vec2 size;

	CaffeineGameObject* parent;

	[[nodiscard]] AABB getWorldSpaceAABB() const;
};

#endif //COLLIDER_HPP
