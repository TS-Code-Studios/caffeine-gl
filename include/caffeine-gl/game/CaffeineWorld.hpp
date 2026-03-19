#ifndef CAFFEINEWORLD_HPP
#define CAFFEINEWORLD_HPP

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <caffeine-gl/game/CaffeineEntity.hpp>
#include <caffeine-gl/game/ComponentPool.hpp>

class CaffeineWorld {
public:
	CaffeineEntity nextFreeID = 0;
	std::vector<CaffeineEntity> availableIDList;

	std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolInterface>> componentPools;

	CaffeineWorld() = default;

	CaffeineEntity createEntity();
	void destroyEntity(CaffeineEntity entity);

	template<typename PooledComponentType>
	void addComponent(CaffeineEntity entity, PooledComponentType component);
	template<typename PooledComponentType>
	PooledComponentType& getComponent(CaffeineEntity entity);
	template<typename PooledComponentType>
	bool hasComponent(CaffeineEntity entity);
	template<typename PooledComponentType>
	void removeComponent(CaffeineEntity entity);

	void removeAllComponentsFromEntity(CaffeineEntity entity);


	template<typename PooledComponentType>
	ComponentPool<PooledComponentType>& getPool();
};

#endif //CAFFEINEWORLD_HPP
