#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "../src/gfx/SpriteRenderer.h"
#include "../src/gfx/ResourceManager.h"

enum Level {
	STANDARD,
	GAPS,
	SPACE_INVADER,
	BOUNCE_GALORE
};

enum Blocks {
	AIR,
	SOLID,
	BREAKABLE_RED,
	BREAKABLE_GREEN,
	BREAKABLE_BLUE,
	BREAKABLE_YELLOW
};

class GameLevel {
public:
	std::vector<GameObject> Bricks;

	GameLevel() = default;

	void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRenderer &renderer);

	bool isCompleted();

private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif