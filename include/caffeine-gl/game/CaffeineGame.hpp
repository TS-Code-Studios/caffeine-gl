#ifndef GAME_H
#define GAME_H

#include "caffeine-gl/gfx/Renderer.hpp"
#include "caffeine-gl/gfx/ResourceManager.hpp"

class ParticleGenerator;

class CaffeineGame {
public:
	float virtualWidth = Renderer::virtualWidth;
	float virtualHeight = Renderer::virtualHeight;

	virtual ~CaffeineGame() {
		std::cout << "Cleaning up game resources..." << std::endl;
		ResourceManager::clear();
	};

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};

#endif //GAME_H
