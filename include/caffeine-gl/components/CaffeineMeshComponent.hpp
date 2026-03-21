#ifndef CAFFEINEMESHCOMPONENT_HPP
#define CAFFEINEMESHCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <caffeine-gl/gfx/CaffeineMesh.hpp>

struct CaffeineMeshComponent : CaffeineComponent {
	CaffeineMesh* mesh = nullptr;
};

#endif //CAFFEINEMESHCOMPONENT_HPP
