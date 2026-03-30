#include <caffeine-gl/gfx/CaffeineFont.hpp>

#include "caffeine-gl/gfx/CaffeineResourceManager.hpp"
#include "caffeine-gl/systems/CaffeineRenderingSystem.hpp"

#include <iostream>

CaffeineFont::CaffeineFont(const std::filesystem::path& path) {
	FT_Library freetype;
	FT_Face face;

	if(FT_Init_FreeType(&freetype)) {
		std::cerr << "ERROR::FREETYPE: Could not init FreeType library" << std::endl;
	}

	if(FT_New_Face(freetype, path.c_str(), 0, &face)) {
		std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for(unsigned char glyph = 0; glyph < 128; glyph++) {
		if(FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load glyph" << std::endl;
			continue;
		}

		CaffeineTexture texture;
		texture.generate(static_cast<GLsizei>(face->glyph->bitmap.width), static_cast<GLsizei>(face->glyph->bitmap.rows), GL_RED, GL_RED, face->glyph->bitmap.buffer);

		characters.try_emplace(
			static_cast<char>(glyph),
			Character(
				std::move(texture),
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			)
		);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(freetype);
}

CaffeineFont::~CaffeineFont() {
	characters.clear();
}