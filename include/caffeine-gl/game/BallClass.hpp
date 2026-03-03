#ifndef BALL_H
#define BALL_H

#include <caffeine-gl/game/CaffeineGameObject.hpp>

class BallClass : public CaffeineGameObject {
public:
	float radius;
	bool stuck;


	BallClass();
	BallClass(glm::vec2 position, float radius, glm::vec2 velocity, Texture sprite);

	glm::vec2 Move(float dt, unsigned int window_width, glm::vec2 player_position, glm::vec2 player_size);



	void Reset(glm::vec2 position, glm::vec2 velocity);
};



#endif //BALL_H
