#ifndef CAFFEINEGAMEOBJECT_H
#define CAFFEINEGAMEOBJECT_H

#include <caffeine-gl/game/Transform.hpp>

// Can't include Collider.hpp here since it would be a circular dependency
class Collider;

class CaffeineGameObject {
public:
	Transform transform;
	Collider* collider;

	virtual ~CaffeineGameObject() = default;

	virtual void OnCollisionEnter(CaffeineGameObject* otherGameObject) {}
	virtual void OnCollisionExit(CaffeineGameObject* otherGameObject) {}
};

#endif