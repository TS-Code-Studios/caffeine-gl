#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"
#include "../game/GameObject.h"

struct Particle {
	glm::vec2 position, velocity;
	glm::vec4 color;
	float lifetime;

	Particle(): position(0.0f), velocity(0.0f), color(1.0f), lifetime(0.0f) { }
};

class ParticleGenerator {
public:
	ParticleGenerator(unsigned int amount);

	void SetTexture(const Texture &texture);
	void SetShader(Shader shader);

	void SetLifetime(float lifetime);
	void SetPositionSpread(int positionSpread);
	void SetColor(glm::vec4 color);

	void Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Draw();

private:
	std::vector<Particle> particles;
	unsigned int amount;
	float lifetime;

	glm::vec2 offset;
	int positionSpread;

	Shader shader;
	Texture texture;
	unsigned int VAO{};

	void init();
	unsigned int firstUnusedParticle();
	void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif //PARTICLEGENERATOR_H
