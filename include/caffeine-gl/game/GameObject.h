#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>

#include "caffeine-gl/game/Transform.h"

#include "caffeine-gl/gfx/Texture.h"
#include "caffeine-gl/gfx/SpriteRenderer.h"


class GameObject {
public:
	virtual ~GameObject() = default;

	Transform transform;

	glm::vec2 velocity;
	glm::vec3 color;
	bool isSolid;
	bool destroyed;

	Texture Sprite;

	GameObject();
	GameObject(glm::vec2 position, float rotation, glm::vec2 scale, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(SpriteRenderer &renderer);
};

#endif