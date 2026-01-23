#include "Game.h"

#include "../gfx/ParticleGenerator.h"
#include "../src/gfx/ResourceManager.h"
#include "GLFW/glfw3.h"


Game::Game(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->state = GAME_ACTIVE;
	this->activeLevel = STANDARD;

	std::fill(std::begin(this->keys), std::end(this->keys), false); // Initialize all keys to false
}

Game::~Game() {
	Renderer->~SpriteRenderer();
}

const glm::vec2 PLAYER_SIZE(150.0f, 30.0f);
const float PLAYER_VELOCITY(500.0f);

const float BALL_RADIUS = 25.0f;
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

void Game::Init() {
	ResourceManager::LoadShader("src/shaders/default.vert", "src/shaders/default.frag",
		nullptr, "sprite");
	ResourceManager::LoadShader("src/shaders/particle.vert", "src/shaders/particle.frag",
		nullptr, "defaultParticleShader");

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
			static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").activate().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);

	ResourceManager::GetShader("defaultParticleShader").activate().setInteger("particleTexture", 0);
	ResourceManager::GetShader("defaultParticleShader").setMatrix4("projectionMatrix", projectionMatrix);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "ball");
	ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");

	ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
	ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");

	BallTrail = new ParticleGenerator (250);
	BallTrail->SetShader(ResourceManager::GetShader("defaultParticleShader"));
	BallTrail->SetTexture(ResourceManager::GetTexture("ball"));

	BallTrail->SetLifetime(1.0f);
	BallTrail->SetPositionSpread(200);


	GameLevel standard; standard.Load("resources/levels/standard.lvl", this->width, this->height / 2);
	GameLevel gaps; gaps.Load("resources/levels/gaps.lvl", this->width, this->height / 2);
	GameLevel space_invader; space_invader.Load("resources/levels/space_invader.lvl", this->width, this->height / 2);
	GameLevel bounce_galore; bounce_galore.Load("resources/levels/bounce_galore.lvl", this->width, this->height / 2);

	this->Levels.push_back(standard);
	this->Levels.push_back(gaps);
	this->Levels.push_back(space_invader);
	this->Levels.push_back(bounce_galore);

	this->activeLevel = BOUNCE_GALORE;
	this->state = GAME_ACTIVE;

	glm::vec2 playerPos = glm::vec2(
		this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallClass(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));
}

void Game::UpdateDimensions(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").setMatrix4("projectionMatrix", projectionMatrix);
}


void Game::ProcessInput(float dt) {
	if(this->state == GAME_ACTIVE) {
		float velocity = PLAYER_VELOCITY * dt;

		if(this->keys[GLFW_KEY_A]) {
			if(Player->position.x >= 0.0f) {
				Player->position.x -= velocity;
				if(Ball->stuck) {
					Ball->position.x -= velocity;
				}
			}
		}
		if(this->keys[GLFW_KEY_D]) {
			if(Player->position.x <= this->width - Player->size.x) {
				Player->position.x += velocity;
				if(Ball->stuck) {
					Ball->position.x += velocity;
				}
			}
		}
		if(this->keys[GLFW_KEY_SPACE]) {
			Ball->stuck = false;
		}
	}
}

void Game::Update(float dt) {
	Ball->Move(dt, this->width, Player->position, PLAYER_SIZE);
	this->DoCollisions();
	BallTrail->Update(dt, *Ball, 2, glm::vec2(Ball->radius));

	if (Ball->position.y >= this->height) {
		resetLevel();
		resetPlayer();
	}
}

void Game::DoCollisions() {
	for (GameObject &box : this->Levels[this->activeLevel].Bricks) {
		if (!box.destroyed) {
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) {

				if (!box.isSolid) {
					box.destroyed = true;
				}

				Direction direction = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);

				if (direction == LEFT || direction == RIGHT) {
					Ball->velocity.x = -Ball->velocity.x;
					float penetration = Ball->radius - std::abs(diff_vector.x);
					if (direction == LEFT) {
						Ball->position.x += penetration;
					}
					else {
						Ball->position.x -= penetration;
					}
				}
				else {
					Ball->velocity.y = -Ball->velocity.y;

					float penetration = Ball->radius - std::abs(diff_vector.y);
					if (direction == UP) {
						Ball->position.y -= penetration;
					}
					else {
						Ball->position.y += penetration;
					}
				}
			}
		}
	}

	Collision result = CheckCollision(*Ball, *Player);
	if(!Ball->stuck && std::get<0>(result)) {
		float centerBoard = Player->position.x + Player->size.x / 2.0;
		float distance = (Ball->position.x + Ball->radius) - centerBoard;
		float percentage = distance / (Player->size.x / 2.0f);

		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->velocity;
		Ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		Ball->velocity.y = -1 * std::abs(Ball->velocity.y);
		Ball->velocity = glm::normalize(Ball->velocity) * glm::length(oldVelocity);
	}
}

Direction Game::VectorDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for(unsigned int i = 0; i < 4; i++) {
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if(dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return static_cast<Direction>(best_match);
}


void Game::Render() {
	if(this->state == GAME_ACTIVE) {
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		   glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		this->Levels[this->activeLevel].Draw(*Renderer);
		Player->Draw(*Renderer);

		BallTrail->Draw();
		Ball->Draw(*Renderer);
	}
}


bool Game::CheckCollision(GameObject &one, GameObject &two) {
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
			two.position.x + two.size.x >= one.position.x;

	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;

	return collisionX && collisionY;
}

Collision Game::CheckCollision(BallClass &ball, GameObject &block) {
	glm::vec2 center(ball.position + ball.radius);

	glm::vec2 block_half_extents(block.size.x / 2.0f, block.size.y / 2.0f);
	glm::vec2 block_center(
		block.position.x + block_half_extents.x,
		block.position.y + block_half_extents.y
	);

	glm::vec2 difference = center - block_center;
	glm::vec2 clamped = glm::clamp(difference, -block_half_extents, block_half_extents);

	glm::vec2 closest = block_center + clamped;

	difference = closest - center;

	if(glm::length(difference) <= ball.radius) {
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else {
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
	}
}

void Game::resetLevel() {
	if(this->activeLevel == STANDARD) {
		this->Levels[STANDARD].Load("resources/levels/standard.lvl", this->width, this->height / 2);
	}
	else if(this->activeLevel == GAPS) {
		this->Levels[GAPS].Load("resources/levels/gaps.lvl", this->width, this->height / 2);
	}
	else if(this->activeLevel == SPACE_INVADER) {
		this->Levels[SPACE_INVADER].Load("resources/levels/space_invader.lvl", this->width, this->height / 2);
	}
	else if(this->activeLevel == BOUNCE_GALORE) {
		this->Levels[BOUNCE_GALORE].Load("resources/levels/bounce_galore.lvl", this->width, this->height / 2);
	} else {
		this->Levels[STANDARD].Load("resources/levels/standard.lvl", this->width, this->height / 2);
	}
}

void Game::resetPlayer() {
	Player->position = glm::vec2(
		this->width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->height - PLAYER_SIZE.y
	);
	Ball->Reset(
		Player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f),
		INITIAL_BALL_VELOCITY
	);
}