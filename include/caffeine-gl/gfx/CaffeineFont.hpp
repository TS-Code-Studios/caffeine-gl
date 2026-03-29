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

	Character(const unsigned int textureID, const glm::ivec2 size, const glm::ivec2 bearing, const FT_Pos advance):
			textureID(textureID),
			size(size),
			bearing(bearing),
			advance(advance) {};

	~Character() {
		if (textureID != 0) {
			glDeleteTextures(1, &textureID);
		}
	}

	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	Character(Character&& other) noexcept {
		textureID = other.textureID;
		size = other.size;
		bearing = other.bearing;
		advance = other.advance;

		other.textureID = 0;
	}

	Character& operator=(Character&& other) noexcept {
		if (this != &other) {
			glDeleteTextures(1, &textureID);

			textureID = other.textureID;
			size = other.size;
			bearing = other.bearing;
			advance = other.advance;

			other.textureID = 0;
		}
		return *this;
	}
};

class CaffeineFont {
public:
	explicit CaffeineFont(const std::filesystem::path& path);
	~CaffeineFont();

	CaffeineFont(const CaffeineFont&) = delete;
	CaffeineFont& operator=(const CaffeineFont&) = delete;

	CaffeineFont(CaffeineFont&& other) noexcept {
		vao = other.vao;
		vbo = other.vbo;
		ebo = other.ebo;
		characters = std::move(other.characters);

		other.vao = 0;
		other.vbo = 0;
		other.ebo = 0;
	}

	CaffeineFont& operator=(CaffeineFont&& other) noexcept {
		vao = other.vao;
		vbo = other.vbo;
		ebo = other.ebo;
		characters = std::move(other.characters);

		other.vao = 0;
		other.vbo = 0;
		other.ebo = 0;

		return *this;
	}

	void renderText(const CaffeineTextComponent& text, CaffeineTransformComponent transform);

private:
	unsigned int vao{}, vbo{}, ebo{};

	std::map<char, Character> characters;
};

#endif //CAFFEINEFONT_HPP
