#ifndef CAFFEINEWORLD_HPP
#define CAFFEINEWORLD_HPP

#include <cstdint>
#include <vector>

using Entity = uint32_t;

class CaffeineWorld {
	Entity nextFreeID = 0;
	std::vector<Entity> availableIDList;

	Entity createEntity();
	void destroyEntity(Entity entity);

	void removeAllComponentsFromEntity(Entity entity);
};

#endif //CAFFEINEWORLD_HPP
