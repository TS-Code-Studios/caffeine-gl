#include <iostream>

#include <caffeine-gl/physics/CollisionSystem.hpp>

std::vector<Collider*> CollisionSystem::colliders;

void CollisionSystem::update(float deltaTime) {
	// Iterate through colliders array
	for(size_t index1 = 0; index1 < colliders.size(); index1++) {
		// For every collider, check for collisions with the colliders after it (to avoid double checking a pair of colliders)
		for(size_t index2 = index1 + 1; index2 < colliders.size(); index2++) {
			// Skip static vs. static collision checks
			if(colliders[index1]->type == STATIC && colliders[index2]->type == STATIC) {
				continue;
			}

			if(checkCollision_AABB(colliders[index1]->getWorldSpaceAABB(), colliders[index2]->getWorldSpaceAABB())) {
				// Once OBBs and SAT collision detection are implemented run that here
				if(colliders[index1]->collisionCallback) {
					colliders[index1]->collisionCallback(*colliders[index2]->parent);
				}
				if(colliders[index2]->collisionCallback) {
					colliders[index2]->collisionCallback(*colliders[index1]->parent);
				}
			}
		}
	}
}

void CollisionSystem::registerCollider(Collider *collider) {
	colliders.push_back(collider);
}

void CollisionSystem::unregisterCollider(const Collider *collider) {
	for(size_t i = 0; i < colliders.size(); i++) {
		if(colliders[i] == collider) {
			colliders[i] = colliders.back();
			colliders.pop_back();
			return;
		}
	}
}



bool CollisionSystem::checkCollision_AABB(AABB a, AABB b) {
	return !(a.max.x <= b.min.x ||
			 a.min.x >= b.max.x ||
			 a.max.y <= b.min.y ||
			 a.min.y >= b.max.y);
}

