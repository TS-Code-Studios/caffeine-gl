#ifndef CAFFEINEVELOCITYCOMPONENT_HPP
#define CAFFEINEVELOCITYCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <glm/glm.hpp>

struct CaffeineVelocityComponent : CaffeineComponent {
	glm::vec2* velocity;

	explicit CaffeineVelocityComponent(glm::vec2* velocity): velocity(velocity) {};
};

#endif //CAFFEINEVELOCITYCOMPONENT_HPP