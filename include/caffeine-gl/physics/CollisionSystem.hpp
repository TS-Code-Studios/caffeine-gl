#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "Collider.hpp"

class CollisionSystem {
public:
	static void update(float deltaTime);

	static void registerCollider(Collider* collider);
	static void unregisterCollider(Collider* collider);

private:
	static std::vector<Collider*> colliders;

	static void checkCollision(const Collider* a, const Collider* b);
};

#endif // COLLISIONSYSTEM_HPP