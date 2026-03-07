#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"

class Texture {
public:
	unsigned int ID{};

	GLsizei width, height;
	GLint format_INTERNAL, format_IMAGE;

	GLint wrap_S, wrap_T;
	GLint filter_MIN, filter_MAX;

	Texture();
	~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) noexcept {
		ID = other.ID;
		other.ID = 0;
	}

	Texture& operator=(Texture&& other) noexcept {
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