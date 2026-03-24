#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <caffeine-gl/gfx/CaffeineShader.hpp>
#include <caffeine-gl/gfx/CaffeineTexture.hpp>

struct CaffeineMaterialComponent : CaffeineComponent {
	CaffeineShader* shader;
	CaffeineTexture* texture;

	CaffeineMaterialComponent(CaffeineShader* shader, CaffeineTexture* texture): shader(shader), texture(texture) {};
};

#endif //MATERIAL_HPP
