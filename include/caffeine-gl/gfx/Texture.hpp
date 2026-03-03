#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
	unsigned int ID;

	unsigned int width, height;
	unsigned int format_INTERNAL, format_IMAGE;

	unsigned int wrap_S, wrap_T;
	unsigned int filter_MIN, filter_MAX;

	Texture();
	void generate(unsigned int width, unsigned int height, const unsigned char* data);
	void bind() const;
};

#endif //TEXTURE_H