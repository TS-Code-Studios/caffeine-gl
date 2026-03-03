#include <caffeine-gl/game/CaffeineGameObject.hpp>

CaffeineGameObject::CaffeineGameObject()
	: position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), isSolid(false), destroyed(false), Sprite() { }

CaffeineGameObject::CaffeineGameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), isSolid(false), destroyed(false), Sprite(sprite) { }

void CaffeineGameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->position, this->size, this->rotation, this->color);
}