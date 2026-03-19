#ifndef GAME_H
#define GAME_H

#include "../systems/CaffeineRenderingSystem.hpp"
#include "caffeine-gl/gfx/ResourceManager.hpp"

class ParticleGenerator;

class CaffeineGame {
public:
	float virtualWidth = CaffeineRenderingSystem::virtualWidth;
	float virtualHeight = CaffeineRenderingSystem::virtualHeight;

	virtual ~CaffeineGame() {
		std::cout << "Cleaning up game resources..." << std::endl;
		ResourceManager::clear();
	};

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};

#endif //GAME_H
