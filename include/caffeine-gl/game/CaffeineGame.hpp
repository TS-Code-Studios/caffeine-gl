#ifndef GAME_H
#define GAME_H

class ParticleGenerator;

class CaffeineGame {
public:
	virtual ~CaffeineGame() = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

#endif //GAME_H
