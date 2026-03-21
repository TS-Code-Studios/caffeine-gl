#ifndef CAFFEINEVELOCITYCOMPONENT_HPP
#define CAFFEINEVELOCITYCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <glm/glm.hpp>

struct CaffeineVelocityComponent : CaffeineComponent {
	glm::vec2 velocity = glm::vec2(0.0f);
};

#endif //CAFFEINEVELOCITYCOMPONENT_HPP