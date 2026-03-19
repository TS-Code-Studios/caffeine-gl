#ifndef COMPONENTPOOLINTERFACE_HPP
#define COMPONENTPOOLINTERFACE_HPP

#include <caffeine-gl/game/CaffeineEntity.hpp>

class ComponentPoolInterface {
public:
	virtual ~ComponentPoolInterface() = default;
	virtual void remove(CaffeineEntity entity);
};

#endif //COMPONENTPOOLINTERFACE_HPP
