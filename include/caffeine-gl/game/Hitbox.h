#ifndef HITBOX_H
#define HITBOX_H

#include "GameObject.h"
#include <box2d/box2d.h>
#include "glm/glm.hpp"

class Hitbox {
public:
	GameObject* owner;
	glm::vec2 scale;
	b2BodyDef body;
};

#endif //HITBOX_H
