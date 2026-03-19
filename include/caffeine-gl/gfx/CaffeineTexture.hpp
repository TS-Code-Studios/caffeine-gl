#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"

class CaffeineTexture {
public:
	unsigned int ID{};

	GLsizei width, height;
	GLint format_INTERNAL, format_IMAGE;

	GLint wrap_S, wrap_T;
	GLint filter_MIN, filter_MAX;

	CaffeineTexture();
	~CaffeineTexture();
	CaffeineTexture(const CaffeineTexture&) = delete;
	CaffeineTexture& operator=(const CaffeineTexture&) = delete;

	CaffeineTexture(CaffeineTexture&& other) noexcept {
		ID = other.ID;
		other.ID = 0;
	}

	CaffeineTexture& operator=(CaffeineTexture&& other) noexcept {
		if (this != &other) {
			glDeleteTextures(1, &ID);
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

	void generate(unsigned int width, unsigned int height, const unsigned char* data);
	void bind() const;
};

#endif //TEXTURE_H