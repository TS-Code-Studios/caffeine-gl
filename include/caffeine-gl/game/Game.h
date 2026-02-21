#ifndef GAME_H
#define GAME_H

#include <box2d/box2d.h>

class ParticleGenerator;

class Game {
public:
	virtual ~Game() = default;

	b2WorldDef worldDef = b2DefaultWorldDef();

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

#endif //GAME_H