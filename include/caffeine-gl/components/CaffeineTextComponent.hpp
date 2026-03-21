#ifndef CAFFEINETEXTCOMPONENT_HPP
#define CAFFEINETEXTCOMPONENT_HPP

#include <string>

#include <caffeine-gl/gfx/CaffeineShader.hpp>

class CaffeineFont;

struct CaffeineTextComponent {
	std::string text;
	CaffeineFont* font;
	CaffeineShader* shader;
	glm::vec3 color;
};

#endif //CAFFEINETEXTCOMPONENT_HPP