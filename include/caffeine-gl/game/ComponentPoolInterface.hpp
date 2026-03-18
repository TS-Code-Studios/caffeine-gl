#ifndef COMPONENTPOOLINTERFACE_HPP
#define COMPONENTPOOLINTERFACE_HPP

#include <cstdint>

using Entity = uint32_t;

class ComponentPoolInterface {
	virtual ~ComponentPoolInterface() = default;
	virtual void remove(Entity entity);
};

#endif //COMPONENTPOOLINTERFACE_HPP
