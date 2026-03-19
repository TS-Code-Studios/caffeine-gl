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

template<typename PooledComponentType>
void CaffeineWorld::addComponent(CaffeineEntity entity, PooledComponentType component) {
	getPool<PooledComponentType>().add(entity, component);
}

template<typename PooledComponentType>
PooledComponentType& CaffeineWorld::getComponent(CaffeineEntity entity) {
	return getPool<PooledComponentType>().get(entity);
}

template<typename PooledComponentType>
bool CaffeineWorld::hasComponent(CaffeineEntity entity) {
	return getPool<PooledComponentType>().has(entity);
}

template<typename PooledComponentType>
void CaffeineWorld::removeComponent(CaffeineEntity entity) {
	getPool<PooledComponentType>().remove(entity);
}

void CaffeineWorld::removeAllComponentsFromEntity(const CaffeineEntity entity) {
	for(auto& [type, pool] : componentPools) {
		pool->remove(entity);
	}
}


template<typename PooledComponentType>
ComponentPool<PooledComponentType> &CaffeineWorld::getPool() {
	const std::type_index type = typeid(PooledComponentType);

	if(componentPools.find(type) == componentPools.end()) {
		componentPools[type] = std::make_unique<ComponentPool<PooledComponentType>>();
	}

	return *static_cast<ComponentPool<PooledComponentType>*>(componentPools[type].get());
}