#ifndef GAME_H
#define GAME_H

class ParticleGenerator;

class Game {
public:
	virtual ~Game() = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

#endif //GAME_H
