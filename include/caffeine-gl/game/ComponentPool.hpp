#ifndef COMPONENTPOOL_HPP
#define COMPONENTPOOL_HPP

#include <unordered_map>
#include <vector>

#include <caffeine-gl/game/ComponentPoolInterface.hpp>

template<typename PooledComponentType>
class ComponentPool final : public ComponentPoolInterface {
public:
	std::vector<PooledComponentType> data;
	std::vector<CaffeineEntity> entities;
	std::unordered_map<CaffeineEntity, size_t> entityToIndex;

	void add(CaffeineEntity entity, PooledComponentType component);
	PooledComponentType& get(CaffeineEntity entity);
	bool has(CaffeineEntity entity);
	void remove(CaffeineEntity entity) override;
};

#endif //COMPONENTPOOL_HPP
