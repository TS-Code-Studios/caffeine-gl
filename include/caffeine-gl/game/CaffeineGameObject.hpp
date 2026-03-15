#ifndef CAFFEINEGAMEOBJECT_H
#define CAFFEINEGAMEOBJECT_H

#include <caffeine-gl/game/Transform.hpp>

#include "caffeine-gl/physics/Collider.hpp"

class CaffeineGameObject {
public:
	Transform transform;
	Collider collider;

	virtual ~CaffeineGameObject() = default;

	virtual void OnCollisionEnter(CaffeineGameObject* otherGameObject) {}
	virtual void OnCollisionExit(CaffeineGameObject* otherGameObject) {}
};

#endif