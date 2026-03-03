#ifndef GAME_H
#define GAME_H

class ParticleGenerator;

class CaffeineGame {
public:
	virtual ~CaffeineGame() = default;

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};

#endif //GAME_H
