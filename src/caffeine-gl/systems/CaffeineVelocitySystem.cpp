#include <caffeine-gl/systems/CaffeineVelocitySystem.hpp>

void CaffeineVelocitySystem::update(CaffeineWorld &world, const float deltaTime) {
	const auto& velocityPool = world.getPool<CaffeineVelocityComponent>();

	for(const CaffeineEntity entity : velocityPool.entities) {
		if(!world.hasComponent<CaffeineTransformComponent>(entity)) continue;

		auto& velocityComponent = world.getComponent<CaffeineVelocityComponent>(entity);
		auto& transformComponent = world.getComponent<CaffeineTransformComponent>(entity);

		transformComponent.position += velocityComponent.velocity * deltaTime;
	}
}
