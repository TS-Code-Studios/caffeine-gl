#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <caffeine-gl/components/CaffeineColliderComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

#include <caffeine-gl/game/CaffeineWorld.hpp>

class CaffeineCollisionSystem {
public:
	static void update(CaffeineWorld& world, float deltaTime);

private:
	[[nodiscard]] static AABB getWorldSpaceAABB(const CaffeineColliderComponent& collider, const CaffeineTransformComponent& transform);

	static bool checkCollision_AABB(AABB a, AABB b);
};

#endif // COLLISIONSYSTEM_HPP