#ifndef CAFFEINECOMPONENTPOOL_HPP
#define CAFFEINECOMPONENTPOOL_HPP

#include <unordered_map>
#include <vector>

#include <caffeine-gl/game/CaffeineComponentPoolInterface.hpp>
#include <caffeine-gl/components/CaffeineComponent.hpp>

template<typename ComponentType>
requires Component<ComponentType>
class CaffeineComponentPool final : public CaffeineComponentPoolInterface {
public:
	std::vector<ComponentType> data;
	std::vector<CaffeineEntity> entities;
	std::unordered_map<CaffeineEntity, size_t> entityToIndex;


	void add(const CaffeineEntity entity, ComponentType component) {
		// Map entity to next free index of data array (since size = last index + 1)
		entityToIndex[entity] = data.size();

		entities.push_back(entity);
		data.push_back(component);
	}

	ComponentType& get(const CaffeineEntity entity) {
		return data[entityToIndex[entity]];
	}

	bool has(const CaffeineEntity entity) {
		return entityToIndex.find(entity) != entityToIndex.end();
	}

	void remove(const CaffeineEntity entity) override {
		const auto entry = entityToIndex.find(entity);
		if(entry == entityToIndex.end()) return;

		size_t index = entry->second;
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
};

#endif //CAFFEINECOMPONENTPOOL_HPP
