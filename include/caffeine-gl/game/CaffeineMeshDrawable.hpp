#ifndef CAFFEINEMESHDRAWABLE_HPP
#define CAFFEINEMESHDRAWABLE_HPP

#include <caffeine-gl/components/Mesh.hpp>
#include <caffeine-gl/components/Material.hpp>

#include <caffeine-gl/game/CaffeineDrawable.hpp>

class CaffeineMeshDrawable final : public CaffeineDrawable {
public:
	CaffeineMeshDrawable(const Mesh &mesh, const Material &material);
	void submitToRenderer() override;

	void setLocation(const glm::vec2 &position);
	void setSize(const glm::vec2 &scale);
	void setRotation(const float &degrees);

	void translate(const glm::vec2 &delta);
	void scale(const glm::vec2 &factor);
	void rotate(const float &degrees);

private:
	const Mesh *mesh;
	Material material;
};

#endif //CAFFEINEMESHDRAWABLE_HPP