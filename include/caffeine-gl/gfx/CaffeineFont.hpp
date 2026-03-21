#ifndef CAFFEINEFONT_HPP
#define CAFFEINEFONT_HPP

#include <filesystem>
#include <iostream>

#include <ft2build.h>
#include <map>

#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <caffeine-gl/components/CaffeineTextComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

struct Character {
	unsigned int textureID;

	glm::ivec2 size;
	glm::ivec2 bearing;
	FT_Pos advance;

	~Character() {
		glDeleteTextures(1, &textureID);
	}
};

class CaffeineFont {
public:
	explicit CaffeineFont(const std::filesystem::path& path);
	~CaffeineFont();

	void renderText(const CaffeineTextComponent& text, CaffeineTransformComponent transform);

private:
	unsigned int vao{}, vbo{}, ebo{};

	std::map<char, Character> characters;
};

#endif //CAFFEINEFONT_HPP
