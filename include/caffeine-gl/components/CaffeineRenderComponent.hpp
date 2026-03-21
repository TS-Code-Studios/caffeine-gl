#ifndef CAFFEINERENDERCOMPONENT_HPP
#define CAFFEINERENDERCOMPONENT_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

struct CaffeineRenderComponent : CaffeineComponent {
	int layer = 0;
	bool visible = true;
};

#endif //CAFFEINERENDERCOMPONENT_HPP
