#include <caffeine-gl/game/CaffeineWorld.hpp>

CaffeineEntity CaffeineWorld::createEntity() {
	// If any IDs have been freed, re-use one of those and remove it from the list of available IDs again
	if(!availableIDList.empty()) {
		const CaffeineEntity e = availableIDList.back();
		availableIDList.pop_back();
		return e;
	}
	// If no entities have been deleted yet, just use the next ID
	return nextFreeID++;
}

void CaffeineWorld::destroyEntity(const CaffeineEntity entity) {
	removeAllComponentsFromEntity(entity);

	availableIDList.push_back(entity);
}

void CaffeineWorld::removeAllComponentsFromEntity(const CaffeineEntity entity) {
	for(auto& [type, pool] : componentPools) {
		pool->remove(entity);
	}
}



void CaffeineWorld::clear() {
	nextFreeID = 0;
	availableIDList.clear();

	for(auto& [type, pool] : componentPools) {
		pool.reset();
	}

	componentPools.clear();
}