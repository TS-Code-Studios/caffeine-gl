#include <caffeine-gl/gfx/CaffeineFont.hpp>

#include "caffeine-gl/systems/CaffeineRenderingSystem.hpp"

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

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		characters.try_emplace(
			glyph,
			Character(
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			)
		);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(freetype);

	const std::vector<uint32_t> indices {0, 1, 2, 1, 2, 3};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CaffeineFont::renderText(const CaffeineTextComponent& text, CaffeineTransformComponent transform) {
	text.shader->activate();
	text.shader->setVector4f("textColor", text.color);
	text.shader->setMatrix4("projectionMatrix", CaffeineRenderingSystem::projectionMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	for(char c : text.text) {
		if (auto entry = characters.find(c); entry != characters.end()) {
			auto& [textureID, size, bearing, advance] = entry->second;

			const float xPos = transform.position.x + static_cast<float>(bearing.x) * transform.size.x;
			const float yPos = transform.position.y + static_cast<float>(size.y - bearing.y) * transform.size.y;

			const float width = static_cast<float>(size.x) * transform.size.x;
			const float height = static_cast<float>(size.y) * transform.size.y;

			const float vertices[4][4] = {
				{xPos,         yPos,            0.0f, 1.0f }, // Bottom left
				{xPos + width, yPos,            1.0f, 1.0f }, // Bottom right
				{xPos,         yPos + height,   0.0f, 0.0f }, // Top left
				{xPos + width, yPos + height,   1.0f, 0.0f }, // Top right
			};

			glBindTexture(GL_TEXTURE_2D, textureID);
			text.shader->setInteger("text", 0);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void*>(nullptr));

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			// @TODO: add rotated text support
			transform.position.x += static_cast<float>(advance >> 6) * transform.size.x;
		} else {
			// @TODO: missing glyph handling
		}
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


CaffeineFont::~CaffeineFont() {
	characters.clear();

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}