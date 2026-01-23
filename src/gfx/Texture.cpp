#include "Texture.h"

#include <glad/glad.h>

Texture::Texture()
	: width(0), height(0), format_INTERNAL(GL_RGB), format_IMAGE(GL_RGB), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_MIN(GL_LINEAR), filter_MAX(GL_LINEAR) {
	glGenTextures(1, &this->ID);
}

void Texture::generate(const unsigned int width, const unsigned int height, const unsigned char* data) {
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->format_INTERNAL, width, height, 0, this->format_IMAGE, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_MIN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_MAX);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}