#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <caffeine-gl/gfx/Shader.hpp>
#include <caffeine-gl/gfx/Texture.hpp>

struct Material {
	Shader* shader = nullptr;
	Texture* texture = nullptr;
};

#endif //MATERIAL_HPP
