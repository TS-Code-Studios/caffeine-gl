#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

#include <caffeine-gl/gfx/Texture.hpp>
#include <caffeine-gl/gfx/SpriteRenderer.hpp>


class CaffeineGameObject {
public:
	virtual ~CaffeineGameObject() = default;

	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	bool isSolid;
	bool destroyed;

	Texture Sprite;

	CaffeineGameObject();
	CaffeineGameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(SpriteRenderer &renderer);
};

#endif