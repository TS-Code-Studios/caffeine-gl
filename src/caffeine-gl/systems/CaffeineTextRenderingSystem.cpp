#include <algorithm>
#include <caffeine-gl/systems/CaffeineTextRenderingSystem.hpp>

#include <caffeine-gl/gfx/CaffeineFont.hpp>


void CaffeineTextRenderingSystem::update(CaffeineWorld &world) {
	const auto& textPool = world.getPool<CaffeineTextComponent>();

	for(const CaffeineEntity entity : textPool.entities) {
		if(!world.hasComponent<CaffeineRenderComponent>(entity)
			|| !world.hasComponent<CaffeineTransformComponent>(entity)) continue;

		auto& renderComponent = world.getComponent<CaffeineRenderComponent>(entity);
		if(!renderComponent.visible) continue;

		auto& textComponent = world.getComponent<CaffeineTextComponent>(entity);
		auto& transformComponent = world.getComponent<CaffeineTransformComponent>(entity);

		textRenderingCommands.push_back({
			renderComponent.layer,

			&textComponent,
			&transformComponent
		});
	};

	flush();
}

void CaffeineTextRenderingSystem::flush() {
	std::sort(textRenderingCommands.begin(), textRenderingCommands.end(),
		[](const TextRenderingCommand& a, const TextRenderingCommand& b) {
			return a.layer < b.layer;
		});

	for(const TextRenderingCommand command : textRenderingCommands) {
		command.text->font->renderText(*command.text, *command.transform);
	}

	textRenderingCommands.clear();
}
