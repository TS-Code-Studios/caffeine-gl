#ifndef COMPONENTPOOL_HPP
#define COMPONENTPOOL_HPP

#include <unordered_map>
#include <vector>

#include <caffeine-gl/game/ComponentPoolInterface.hpp>

template<typename pooledComponentType>
class ComponentPool final : public ComponentPoolInterface {
public:
	std::vector<pooledComponentType> data;
	std::vector<Entity> entities;
	std::unordered_map<Entity, size_t> entityToIndex;

	void add(Entity entity, pooledComponentType component);
	pooledComponentType& get(Entity entity);
	bool has(Entity entity);
	void remove(Entity entity) override;
};

#endif //COMPONENTPOOL_HPP
