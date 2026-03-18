#include <caffeine-gl/game/CaffeineWorld.hpp>

CaffeineWorld::Entity CaffeineWorld::createEntity() {
	// If any IDs have been freed, re-use one of those and remove it from the list of available IDs again
	if(!availableIDList.empty()) {
		const Entity e = availableIDList.back();
		availableIDList.pop_back();
		return e;
	}
	// If no entities have been deleted yet, just use the next ID
	return nextFreeID++;
}

void CaffeineWorld::destroyEntity(const Entity entity) {
	removeAllComponentsFromEntity(entity);

	availableIDList.push_back(entity);
}
