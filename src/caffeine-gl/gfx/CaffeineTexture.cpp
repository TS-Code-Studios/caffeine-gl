#include <caffeine-gl/gfx/CaffeineTexture.hpp>

#include <iostream>

#include <glad/glad.h>

CaffeineTexture::CaffeineTexture()
	: width(0), height(0), format_INTERNAL(GL_RGB), format_IMAGE(GL_RGB), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_MIN(GL_LINEAR), filter_MAX(GL_LINEAR) {
	glGenTextures(1, &this->ID);
}


CaffeineTexture::~CaffeineTexture() {
	glDeleteTextures(1, &this->ID);
}


void CaffeineTexture::generate(const unsigned int width, const unsigned int height, const unsigned char* data) {
	this->width = static_cast<GLsizei>(width);
	this->height = static_cast<GLsizei>(height);

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, this->format_INTERNAL, this->width, this->height, 0, this->format_IMAGE, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_MIN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_MAX);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void CaffeineTexture::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}