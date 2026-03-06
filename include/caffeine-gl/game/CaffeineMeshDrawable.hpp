#ifndef CAFFEINEMESHDRAWABLE_HPP
#define CAFFEINEMESHDRAWABLE_HPP

#include <caffeine-gl/gfx/Mesh.hpp>
#include <caffeine-gl/gfx/Material.hpp>

#include <caffeine-gl/game/CaffeineDrawable.hpp>

class CaffeineMeshDrawable final : CaffeineDrawable {
public:
	CaffeineMeshDrawable(const Mesh &mesh, const Material &material);
	void submitToRenderer(Renderer &renderer) override;

	void move(const glm::vec2 &delta);
	void scale(const glm::vec2 &factor);
	void rotate(const float &radians);

private:
	const Mesh *mesh;
	Material material;
	Transform transform;
};

#endif //CAFFEINEMESHDRAWABLE_HPP
