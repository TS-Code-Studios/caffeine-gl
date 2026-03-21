#ifndef CAFFEINEVELOCITYSYSTEM_HPP
#define CAFFEINEVELOCITYSYSTEM_HPP

#include <caffeine-gl/game/CaffeineWorld.hpp>

#include <caffeine-gl/components/CaffeineVelocityComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

class CaffeineVelocitySystem {
public:
	static void update(CaffeineWorld& world, float deltaTime);
};

#endif //CAFFEINEVELOCITYSYSTEM_HPP
