#ifndef CAFFEINEDRAWABLE_HPP
#define CAFFEINEDRAWABLE_HPP

#include <caffeine-gl/game/CaffeineGameObject.hpp>
#include <caffeine-gl/gfx/Renderer.hpp>

class CaffeineDrawable : public CaffeineGameObject {
public:
	bool visible = true;

	~CaffeineDrawable() override = default;

	virtual void submitToRenderer() = 0;
};

#endif //CAFFEINEDRAWABLE_HPP
