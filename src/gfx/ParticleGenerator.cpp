#include "ParticleGenerator.h"
#include <random>
#include <iostream>

ParticleGenerator::ParticleGenerator(unsigned int amount) {
	this->amount = amount;
	lifetime = 1.0f;
	this->init();
}

void ParticleGenerator::init() {
	unsigned int VBO;
	float square_vertices[] ={
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f
	};


	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr));
	glBindVertexArray(0);

	for(int i = 0; i < this->amount; i++) {
		this->particles.push_back(Particle());
	}
}


void ParticleGenerator::Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset) {
	for(unsigned int i = 0; i < newParticles; i++) {
		this->respawnParticle(particles[this->firstUnusedParticle()], object, offset);
	}

	for(unsigned int i = 0; i < this->amount; i++) {
		Particle &p = this->particles[i];
		p.lifetime -= dt;
		if(p.lifetime > 0.0f) {
			p.velocity = object.velocity * 0.1f;
			p.position -= p.velocity * dt;
			p.color.a = p.lifetime / this->lifetime;
		}
	}
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle() {
	for(unsigned int i = lastUsedParticle; i < this->amount; i++) {
		if(this->particles[i].lifetime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}

	for(unsigned int i = 0; i < lastUsedParticle; i++) {
		if(this->particles[i].lifetime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}


void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 1);

	float randomX = ((rand() % positionSpread) - 50) / 10.0f;
	float randomY = ((rand() % positionSpread) - 50) / 10.0f;

	if(distr(gen) == 0) {
		randomX = randomX * -1;
	}

	if(distr(gen) == 0) {
		randomY = randomY * -1;
	}


	float rColorR = 0.5f + ((rand() % 1) / 100.0f);
	float rColorG = 0.5f + ((rand() % 1000) / 100.0f);
	float rColorB = 0.5f + ((rand() % 1) / 100.0f);

	particle.position = object.position + glm::vec2(randomX, randomY) + offset;
	particle.color = glm::vec4(rColorR, rColorG, rColorB, 1.0f);
	particle.lifetime = this->lifetime;
	particle.velocity = object.velocity * 0.1f;
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.activate();

	for(Particle particle : this->particles) {
		if(particle.lifetime > 0.0f) {
			shader.setVector2f("offset", particle.position);
			shader.setVector4f("color", particle.color);
			this->texture.bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::SetTexture(const Texture &texture) {
	this->texture = texture;
}

void ParticleGenerator::SetShader(const Shader shader) {
	this->shader = shader;
}

void ParticleGenerator::SetLifetime(float lifetime) {
	this->lifetime = lifetime;
}

void ParticleGenerator::SetPositionSpread(int positionSpread) {
	this->positionSpread = positionSpread;
}