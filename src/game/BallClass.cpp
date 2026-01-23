#include "BallClass.h"


BallClass::BallClass(): GameObject(), radius(12.5f), stuck(true) { }

BallClass::BallClass(glm::vec2 position, float radius, glm::vec2 velocity, Texture sprite)
		: GameObject(position, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity),
		radius(radius), stuck(true) { }

glm::vec2 BallClass::Move(float dt, unsigned int window_width, glm::vec2 player_position, glm::vec2 player_size) {
	if(!this->stuck) {
		this->position += this->velocity * dt;
		if(this->position.x <= 0.0f) {
			this->velocity.x = -this->velocity.x;
			this->position.x = 0.0f;
		}
		else if(this->position.x + this->size.x >= window_width) {
			this->velocity.x = -this->velocity.x;
			this->position.x = window_width - this->size.x;
		}
		if(this->position.y <= 0.0f) {
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}
		if(this->position.y >= player_position.y + player_size.y) {
			this->stuck = true;
			this->velocity = glm::vec2(100.0f, -350.0f);
			this->position = player_position + glm::vec2(player_size.x / 2.0f - this->radius, -this->radius * 2.0f);
		}

		/*
		if(this->position.y + (this->radius * 2) >= player_position.y && (this->position.x >= player_position.x && this->position.x <= player_position.x + player_size.x)) {
			this->velocity.y = -this->velocity.y;
			const float directionMultiplier = (this->velocity.x >= 0)? 1 : -1;

			this->velocity.x = directionMultiplier * 10.0f * std::abs((this->position.x + this->radius) - (player_position.x + (player_size.x / 2)));
			this->position.y = player_position.y - (this->radius * 2);
		}*/
	}
	return this->position;
}

void BallClass::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->position = position;
	this->velocity = velocity;
}