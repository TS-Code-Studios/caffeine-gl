#ifndef CAFFEINECOLLIDERCOMPONENT_HPP
#define CAFFEINECOLLIDERCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <glm/glm.hpp>

#include <caffeine-gl/game/CaffeineEntity.hpp>

struct AABB {
	glm::vec2 min;
	glm::vec2 max;
};

enum ColliderType {
	STATIC,
	DYNAMIC
};
enum ColliderShape {
	QUAD,
	CIRCLE
};

struct CaffeineColliderComponent : CaffeineComponent {
	ColliderType type = STATIC;
	ColliderShape shape = QUAD;

	bool enabled = false;

	glm::vec2 offset = glm::vec2(0.0f);
	glm::vec2 size = glm::vec2(1.0f);

	std::function<void(CaffeineEntity thisEntity, CaffeineEntity otherEntity)> collisionCallback;
};

#endif //CAFFEINECOLLIDERCOMPONENT_HPP
