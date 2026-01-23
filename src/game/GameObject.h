#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../src/gfx/Texture.h"
#include "../src/gfx/SpriteRenderer.h"


class GameObject {
public:
	virtual ~GameObject() = default;

	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	bool isSolid;
	bool destroyed;

	Texture Sprite;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(SpriteRenderer &renderer);
};

#endif