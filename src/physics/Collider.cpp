#include <iostream>
#include <caffeine-gl/physics/Collider.hpp>

#include <caffeine-gl/game/CaffeineGameObject.hpp>

#include <caffeine-gl/physics/CollisionSystem.hpp>

Collider::Collider(CaffeineGameObject* parent, const ColliderType type, const ColliderShape shape, const glm::vec2 offset, const glm::vec2 size) {
	this->parent = parent;

	this->type = type;
	this->shape = shape;

	this->offset = offset;
	this->size = size;
}


AABB Collider::getWorldSpaceAABB() const {
	AABB result{};

	result.min = glm::vec2(parent->transform.position + offset - size / 2.0f);
	result.max = glm::vec2(parent->transform.position + offset + size / 2.0f);

	return result;
}

void Collider::enable() {
	if(!enabled) {
		CollisionSystem::registerCollider(this);
		enabled = true;
	}
}

void Collider::disable() {
	if(enabled) {
		CollisionSystem::unregisterCollider(this);
		enabled = false;
	}
}
