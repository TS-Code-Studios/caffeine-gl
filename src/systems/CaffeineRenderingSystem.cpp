#include <caffeine-gl/systems/CaffeineRenderingSystem.hpp>

#include <caffeine-gl/components/CaffeineRenderComponent.hpp>


void CaffeineRenderingSystem::update(CaffeineWorld &world) {
	const auto& renderPool = world.getPool<CaffeineRenderComponent>();

	// Iterate through all entities with a CaffeineRenderComponent
	for(const CaffeineEntity entity : renderPool.entities) {
		// Skip any entities set to invisible
		if(!world.getComponent<CaffeineRenderComponent>(entity).visible) continue;
		// Also skip any entities without a proper mesh, material, or transform component
		if(!world.hasComponent<CaffeineMeshComponent>(entity) ||
			!world.hasComponent<CaffeineMaterialComponent>(entity) ||
			!world.hasComponent<CaffeineTransformComponent>(entity)) continue;

		auto& meshComponent = world.getComponent<CaffeineMeshComponent>(entity);
		auto& materialComponent = world.getComponent<CaffeineMaterialComponent>(entity);
		auto& transformComponent = world.getComponent<CaffeineTransformComponent>(entity);

		renderingCommands.push_back({
			meshComponent.mesh,
			materialComponent.material,
			transformComponent
		});
	}

	flush();
}


void CaffeineRenderingSystem::flush() {
	for(auto& [mesh, material, transform] : renderingCommands) {

		material->shader->activate();

		material->shader->setMatrix4("projectionMatrix", projectionMatrix, true);

		material->shader->setMatrix4("modelMatrix", transform.getModelMatrix(), true);

		if(material->texture) {
			glActiveTexture(GL_TEXTURE0);
			material->shader->setInteger("image", 0);
			material->texture->bind();
		}

		mesh->draw();
	}

	renderingCommands.clear();
}
