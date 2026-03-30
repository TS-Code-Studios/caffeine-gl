#ifndef CAFFEINEFONT_HPP
#define CAFFEINEFONT_HPP

#include <filesystem>

#include <ft2build.h>
#include <map>

#include FT_FREETYPE_H

#include <glm/glm.hpp>

#include <caffeine-gl/gfx/CaffeineTexture.hpp>

#include <caffeine-gl/components/CaffeineTextComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>

struct Character {
	CaffeineTexture texture;

	glm::ivec2 size{};
	glm::ivec2 bearing{};
	FT_Pos advance;

	Character(CaffeineTexture&& texture, const glm::ivec2 size, const glm::ivec2 bearing, const FT_Pos advance):
			texture(std::move(texture)),
			size(size),
			bearing(bearing),
			advance(advance) {};

	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	Character(Character&& other) noexcept {
		texture = std::move(other.texture);
		size = other.size;
		bearing = other.bearing;
		advance = other.advance;
	}

	Character& operator=(Character&& other) noexcept {
		if (this != &other) {
			texture = std::move(other.texture);
			size = other.size;
			bearing = other.bearing;
			advance = other.advance;
		}
		return *this;
	}
};

class CaffeineFont {
public:
	std::map<char, Character> characters;

	explicit CaffeineFont(const std::filesystem::path& path);
	~CaffeineFont();

	CaffeineFont(const CaffeineFont&) = delete;
	CaffeineFont& operator=(const CaffeineFont&) = delete;

	CaffeineFont(CaffeineFont&& other) noexcept {
		characters = std::move(other.characters);
	}

	CaffeineFont& operator=(CaffeineFont&& other) noexcept {
		characters = std::move(other.characters);

		return *this;
	}
};

#endif //CAFFEINEFONT_HPP
