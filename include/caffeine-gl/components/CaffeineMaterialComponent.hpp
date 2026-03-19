#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <caffeine-gl/gfx/CaffeineShader.hpp>
#include <caffeine-gl/gfx/CaffeineTexture.hpp>

struct CaffeineMaterialComponent {
	CaffeineShader* shader;
	CaffeineTexture* texture;
};

#endif //MATERIAL_HPP
