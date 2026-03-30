#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class CaffeineTexture {
public:
	unsigned int ID{};

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

	void generate(GLsizei width, GLsizei height, GLint internalFormat, GLint imageFormat, const unsigned char* data) const;
	void setTextureParameter(GLenum parameter, GLint value) const;

	void bind() const;
	static void unbind();
};

#endif //TEXTURE_H