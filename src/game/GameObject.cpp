#include "../include/caffeine-gl/game/GameObject.h"

GameObject::GameObject()
	: velocity(0.0f), color(1.0f), isSolid(false), destroyed(false), Sprite() { }

GameObject::GameObject(glm::vec2 position, float rotation, glm::vec2 scale, Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: transform(position, rotation, scale), velocity(velocity), color(color), isSolid(false), destroyed(false), Sprite(sprite) { }

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->position, this->size, this->rotation, this->color);
}