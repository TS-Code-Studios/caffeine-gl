#ifndef GAME_H
#define GAME_H

#include "BallClass.h"
#include "../gfx/SpriteRenderer.h"
#include "GameLevel.h"

class ParticleGenerator;

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Game {
public:
	SpriteRenderer* Renderer;
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	std::vector<GameLevel> Levels;
	Level activeLevel;

	GameObject* Player;
	BallClass* Ball;
	ParticleGenerator *BallTrail;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void UpdateDimensions(unsigned int width, unsigned int height);

	void DoCollisions();

	void Render();

	static Direction VectorDirection(glm::vec2 target);
	static bool CheckCollision(GameObject &one, GameObject &two);
	static Collision CheckCollision(BallClass &ball, GameObject &block);

	void resetLevel();
	void resetPlayer();
};

#endif //GAME_H
