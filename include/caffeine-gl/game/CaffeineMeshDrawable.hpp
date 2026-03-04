#ifndef CAFFEINEMESHDRAWABLE_HPP
#define CAFFEINEMESHDRAWABLE_HPP

#include <caffeine-gl/gfx/Mesh.hpp>
#include <caffeine-gl/gfx/Material.hpp>

#include <caffeine-gl/game/CaffeineDrawable.hpp>

class CaffeineMeshDrawable final : CaffeineDrawable {
public:
	Mesh mesh;
	Material material;

	CaffeineMeshDrawable();
	void submitToRenderer(Renderer &renderer) override;
};

#endif //CAFFEINEMESHDRAWABLE_HPP
