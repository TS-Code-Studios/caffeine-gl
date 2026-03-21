#ifndef CAFFEINEWORLD_HPP
#define CAFFEINEWORLD_HPP

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <caffeine-gl/game/CaffeineEntity.hpp>
#include <caffeine-gl/game/CaffeineComponentPool.hpp>

class CaffeineWorld {
public:
	CaffeineEntity nextFreeID = 0;
	std::vector<CaffeineEntity> availableIDList;

	std::unordered_map<std::type_index, std::unique_ptr<CaffeineComponentPoolInterface>> componentPools;

	CaffeineWorld() = default;

	CaffeineEntity createEntity();
	void destroyEntity(CaffeineEntity entity);

	template<typename ComponentType>
	void addComponent(CaffeineEntity entity, ComponentType component) {
		getPool<ComponentType>().add(entity, component);
	}

	template<typename ComponentType>
	ComponentType& getComponent(CaffeineEntity entity) {
		return getPool<ComponentType>().get(entity);
	}

	template<typename ComponentType>
	bool hasComponent(CaffeineEntity entity) {
		return getPool<ComponentType>().has(entity);
	}

	template<typename ComponentType>
	void removeComponent(CaffeineEntity entity) {
		getPool<ComponentType>().remove(entity);
	}

	void removeAllComponentsFromEntity(const CaffeineEntity entity);

	template<typename ComponentType>
	CaffeineComponentPool<ComponentType>& getPool() {
		const std::type_index type = typeid(ComponentType);

		if(componentPools.find(type) == componentPools.end()) {
			componentPools[type] = std::make_unique<CaffeineComponentPool<ComponentType>>();
		}

		return *static_cast<CaffeineComponentPool<ComponentType>*>(componentPools[type].get());
	}

	void clear();
};

#endif //CAFFEINEWORLD_HPP
