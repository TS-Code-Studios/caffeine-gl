#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Shader.h"
#include "Texture.h"

class SpriteRenderer {
public:
	explicit SpriteRenderer(Shader &shader);
	~SpriteRenderer();


	void DrawSprite (Texture &texture,
			glm::vec2 position,
			glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
			glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	unsigned int quadVAO;

	void initRenderData();
};

#endif //SPRITE_RENDERER_H