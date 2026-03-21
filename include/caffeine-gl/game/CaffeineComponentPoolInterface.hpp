#ifndef CAFFEINECOMPONENTPOOLINTERFACE_HPP
#define CAFFEINECOMPONENTPOOLINTERFACE_HPP

#include <caffeine-gl/game/CaffeineEntity.hpp>

class CaffeineComponentPoolInterface {
public:
	virtual ~CaffeineComponentPoolInterface() = default;
	virtual void remove(CaffeineEntity entity) = 0;
};

#endif //CAFFEINECOMPONENTPOOLINTERFACE_HPP
