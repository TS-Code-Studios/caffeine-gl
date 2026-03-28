#ifndef CAFFEINETEXTCOMPONENT_HPP
#define CAFFEINETEXTCOMPONENT_HPP

#include <string>

#include <caffeine-gl/components/CaffeineComponent.hpp>

#include <caffeine-gl/gfx/CaffeineShader.hpp>
#include <utility>

class CaffeineFont;

struct CaffeineTextComponent : CaffeineComponent {
	std::string text;
	CaffeineFont* font;
	CaffeineShader* shader;
	glm::vec3 color;

	CaffeineTextComponent(std::string text, CaffeineFont* font, CaffeineShader* shader, const glm::vec3 color): text(std::move(text)), font(font), shader(shader), color(color) {};
};

#endif //CAFFEINETEXTCOMPONENT_HPP