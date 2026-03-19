#ifndef CAFFEINEMATERIAL_HPP
#define CAFFEINEMATERIAL_HPP

#include <caffeine-gl/gfx/CaffeineShader.hpp>
#include <caffeine-gl/gfx/CaffeineTexture.hpp>

struct CaffeineMaterial {
	CaffeineShader* shader;
	CaffeineTexture* texture;
};

#endif //CAFFEINEMATERIAL_HPP