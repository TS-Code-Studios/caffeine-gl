#include <caffeine-gl/gfx/CaffeineTexture.hpp>

#include <glad/glad.h>

CaffeineTexture::CaffeineTexture() {
	glGenTextures(1, &this->ID);
}


CaffeineTexture::~CaffeineTexture() {
	glDeleteTextures(1, &this->ID);
}


void CaffeineTexture::generate(const GLsizei width, const GLsizei height, const GLint internalFormat, const GLint imageFormat, const unsigned char* data) const {
	bind();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unbind();
}

void CaffeineTexture::setTextureParameter(const GLenum parameter, const GLint value) const {
	bind();
	glTexParameteri(GL_TEXTURE_2D, parameter, value);
	unbind();
}


void CaffeineTexture::bind() const {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void CaffeineTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

