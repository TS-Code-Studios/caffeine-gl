#ifndef CAFFEINEMESHCOMPONENT_HPP
#define CAFFEINEMESHCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <caffeine-gl/gfx/CaffeineMesh.hpp>

struct CaffeineMeshComponent : CaffeineComponent {
	CaffeineMesh* mesh = nullptr;

	explicit CaffeineMeshComponent(CaffeineMesh* mesh): mesh(mesh) {};
};

#endif //CAFFEINEMESHCOMPONENT_HPP
