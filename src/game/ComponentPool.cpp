#include <caffeine-gl/game/ComponentPool.hpp>

template<typename pooledComponentType>
void ComponentPool<pooledComponentType>::add(const Entity entity, pooledComponentType component) {
	// Map entity to next free index of data array (since size = last index + 1)
	entityToIndex[entity] = data.size();

	entities.push_back(entity);
	data.push_back(component);
}

template<typename pooledComponentType>
pooledComponentType& ComponentPool<pooledComponentType>::get(const Entity entity) {
	return data[entityToIndex[entity]];
}

template<typename pooledComponentType>
bool ComponentPool<pooledComponentType>::has(const Entity entity) {
	return entityToIndex.find(entity) != entityToIndex.end();
}

template<typename pooledComponentType>
void ComponentPool<pooledComponentType>::remove(const Entity entity) {
	auto entry = entityToIndex.find(entity);
	if(entry == entityToIndex.end()) return;

	size_t index = it->second;
	size_t lastIndex = data.size() - 1;

	// Overwrite the entries that should be deleted with the ones at the end of the arrays
	data[index] = data[lastIndex];
	entities[index] = entities[lastIndex];
	// Remap the entity that has been moved to fill the gap to its new index
	entityToIndex[entities[index]] = index;

	// Delete the old entries
	data.pop_back();
	entities.pop_back();
	entityToIndex.erase(entity);
}


