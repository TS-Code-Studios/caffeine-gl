#ifndef CAFFEINERENDERCOMPONENT_HPP
#define CAFFEINERENDERCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

struct CaffeineRenderComponent : CaffeineComponent {
	int layer = 0;
	bool visible = true;

	CaffeineRenderComponent() = default;

	CaffeineRenderComponent(const int layer, const bool visible): layer(layer), visible(visible) {};
};

#endif //CAFFEINERENDERCOMPONENT_HPP
