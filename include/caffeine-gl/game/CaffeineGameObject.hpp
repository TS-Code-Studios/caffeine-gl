#ifndef CAFFEINEGAMEOBJECT_H
#define CAFFEINEGAMEOBJECT_H

#include <caffeine-gl/game/Transform.hpp>

class CaffeineGameObject {
public:
	Transform transform;

	virtual ~CaffeineGameObject() = default;
};

#endif