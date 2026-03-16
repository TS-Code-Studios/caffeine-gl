#include <iostream>

#include <caffeine-gl/physics/CollisionSystem.hpp>

std::vector<Collider*> CollisionSystem::colliders;

void CollisionSystem::update(float deltaTime) {
		for(size_t index = 1; index < colliders.size(); index++) {
			checkCollision(colliders[0], colliders[index]);
		}
}

void CollisionSystem::registerCollider(Collider *collider) {
	colliders.push_back(collider);
}

void CollisionSystem::unregisterCollider(Collider *collider) {
	for(size_t i = 0; i < colliders.size(); i++) {
		if(colliders[i] == collider) {
			colliders[i] = colliders.back();
			colliders.pop_back();
			return;
		}
	}
}



void CollisionSystem::checkCollision(const Collider* a, const Collider* b) {
	auto [a_min, a_max] = a->getWorldSpaceAABB();
	auto [b_min, b_max] = b->getWorldSpaceAABB();

	std::cout << "x coords: " << a_min.x << " " << a_max.x << " " << b_min.x << " " << b_max.x << std::endl;
	std::cout << "y coords: " << a_min.y << " " << a_max.y << " " << b_min.y << " " << b_max.y << std::endl;

	bool collisionX = false;
	bool collisionY = false;

	collisionX = a_max.x >= b_min.x && b_max.x >= a_min.x;
	collisionY = a_max.y >= b_min.y && b_max.y >= a_min.y;

	if(collisionX && collisionY) {
		std::cout << "collision of" << a << b << std::endl;
	}
}

