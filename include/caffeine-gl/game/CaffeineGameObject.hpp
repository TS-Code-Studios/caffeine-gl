#ifndef CAFFEINEGAMEOBJECT_H
#define CAFFEINEGAMEOBJECT_H

#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

// Can't include Collider.hpp here since it would be a circular dependency
class Collider;

class CaffeineGameObject {
public:
	CaffeineTransformComponent transform;
	Collider* collider;

	virtual ~CaffeineGameObject() = default;

	virtual void OnCollisionEnter(CaffeineGameObject* otherGameObject) {}
	virtual void OnCollisionExit(CaffeineGameObject* otherGameObject) {}
};

#endif