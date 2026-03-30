#include <algorithm>

#include <caffeine-gl/systems/CaffeineTextRenderingSystem.hpp>

#include <caffeine-gl/gfx/CaffeineFont.hpp>
#include <caffeine-gl/gfx/CaffeineResourceManager.hpp>

#include <caffeine-gl/systems/CaffeineRenderingSystem.hpp>

std::vector<TextRenderingCommand> CaffeineTextRenderingSystem::textRenderingCommands;

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
	std::ranges::sort(textRenderingCommands,
	                  [](const TextRenderingCommand& a, const TextRenderingCommand& b) {
		                  return a.layer < b.layer;
	                  });

	for(const TextRenderingCommand command : textRenderingCommands) {
		command.text->shader->activate();
		command.text->shader->setVector4f("textColor", command.text->color);
		command.text->shader->setMatrix4("projectionMatrix", CaffeineRenderingSystem::projectionMatrix);

		glActiveTexture(GL_TEXTURE0);
		command.text->shader->setInteger("text", 0);

		glm::vec2 cursor = command.transform->position;

		for(char c : command.text->text) {
			auto modelMatrix = glm::mat4(1.0f);
			if (auto entry = command.text->font->characters.find(c); entry != command.text->font->characters.end()) {

				auto& [texture, size, bearing, advance] = entry->second;

				const float xPos =
					cursor.x +
						(static_cast<float>(bearing.x) + static_cast<float>(size.x) * 0.5f) * command.transform->size.x;

				const float yPos =
					cursor.y -
						(static_cast<float>(size.y) - static_cast<float>(bearing.y)) * command.transform->size.y +
							static_cast<float>(size.y) * command.transform->size.y * 0.5;

				const float width = static_cast<float>(size.x) * command.transform->size.x;
				const float height = static_cast<float>(size.y) * command.transform->size.y;

				modelMatrix = glm::translate(modelMatrix, glm::vec3(xPos, yPos, 0.0f));
				modelMatrix = glm::rotate(modelMatrix, glm::radians(command.transform->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(width, height, 1.0f));

				command.text->shader->setMatrix4("modelMatrix", modelMatrix);

				texture.bind();

				CaffeineResourceManager::getMesh("quad").draw();

				// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				// @TODO: add rotated text support
				cursor.x += static_cast<float>(advance >> 6) * command.transform->size.x;
			} else {
				// @TODO: missing glyph handling
			}
		}
	}

	textRenderingCommands.clear();
}
