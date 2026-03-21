#include <iostream>

#include <caffeine-gl/systems/CaffeineCollisionSystem.hpp>

void CaffeineCollisionSystem::update(CaffeineWorld& world) {
	const auto& colliderPool = world.getPool<CaffeineColliderComponent>();

	// Iterate through colliders array
	for(size_t index1 = 0; index1 < colliderPool.entities.size(); index1++) {
		const CaffeineEntity entity1 = colliderPool.entities[index1];

		const auto& colliderComponent_1 = world.getComponent<CaffeineColliderComponent>(entity1);
		if(!colliderComponent_1.enabled) continue;

		if(!world.hasComponent<CaffeineTransformComponent>(entity1)) continue;

		for(size_t index2 = index1 + 1; index2 < colliderPool.entities.size(); index2++) {
			const CaffeineEntity entity2 = colliderPool.entities[index2];

			if(entity1 == entity2) continue;

			const auto& colliderComponent_2 = world.getComponent<CaffeineColliderComponent>(entity2);
			if(!colliderComponent_2.enabled) continue;
			if(colliderComponent_1.type == STATIC && colliderComponent_2.type == STATIC) continue;

			if(!world.hasComponent<CaffeineTransformComponent>(entity1)) continue;

			auto& transformComponent_1 = world.getComponent<CaffeineTransformComponent>(entity1);
			auto& transformComponent_2 = world.getComponent<CaffeineTransformComponent>(entity2);

			if(checkCollision_AABB(
				getWorldSpaceAABB(colliderComponent_1, transformComponent_1),
				getWorldSpaceAABB(colliderComponent_2, transformComponent_2))) {
				if(colliderComponent_1.collisionCallback) colliderComponent_1.collisionCallback(entity1, entity2);
				if(colliderComponent_2.collisionCallback) colliderComponent_2.collisionCallback(entity2, entity1);
			}
		}
	}
}

AABB CaffeineCollisionSystem::getWorldSpaceAABB(const CaffeineColliderComponent& collider, const CaffeineTransformComponent& transform) {
	AABB result{};

	result.min = glm::vec2(transform.position + collider.offset - collider.size / 2.0f);
	result.max = glm::vec2(transform.position + collider.offset + collider.size / 2.0f);

	return result;
};

bool CaffeineCollisionSystem::checkCollision_AABB(const AABB a, const AABB b) {
	return !(a.max.x <= b.min.x ||
			 a.min.x >= b.max.x ||
			 a.max.y <= b.min.y ||
			 a.min.y >= b.max.y);
}

