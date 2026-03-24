#ifndef CAFFEINETEXTRENDERINGSYSTEM_HPP
#define CAFFEINETEXTRENDERINGSYSTEM_HPP

#include <caffeine-gl/game/CaffeineWorld.hpp>

#include <caffeine-gl/components/CaffeineTextComponent.hpp>
#include <caffeine-gl/components/CaffeineTransformComponent.hpp>
#include <caffeine-gl/components/CaffeineRenderComponent.hpp>

struct TextRenderingCommand {
	int layer;

	CaffeineTextComponent* text;
	CaffeineTransformComponent* transform;
};

class CaffeineTextRenderingSystem {
public:
	static void update(CaffeineWorld& world);

private:
	static std::vector<TextRenderingCommand> textRenderingCommands;

	static void flush();
};

#endif //CAFFEINETEXTRENDERINGSYSTEM_HPP
