#include <caffeine-gl/physics/Collider.hpp>

AABB Collider::getWorldSpaceAABB() const {
	AABB result;

	result.min = glm::vec2(parent->transform.position + offset - size / 2.0f);
	result.max = glm::vec2(parent->transform.position + offset + size / 2.0f);

	return result;
}
