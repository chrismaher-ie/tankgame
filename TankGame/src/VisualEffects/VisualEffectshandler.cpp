#include "VisualEffectsHandler.h"

VisualEffectsHandler::VisualEffectsHandler()

{
	trackTexture.loadFromFile("Assets/Textures/Track.png");
	addEffect(TRACKTYPE, sf::Vector2f(0.f, 0.f));
}

VisualEffectsHandler::~VisualEffectsHandler()
{
	bottomEffectList.clear();
	topEffectList.clear();
}

void VisualEffectsHandler::update()
{
	for (auto& effect : bottomEffectList) {
		effect->update();
	}
	for (auto& effect : topEffectList) {
		effect->update();
	}

	bottomEffectList.remove_if([&](const std::unique_ptr<Effect> &effect) -> bool { return effect->shouldDelete(); });
	topEffectList.remove_if([&](const std::unique_ptr<Effect> &effect) -> bool { return effect->shouldDelete(); });
}

void VisualEffectsHandler::drawBottomEffects(sf::RenderWindow & window)
{
	for (auto& effect : bottomEffectList) {
		window.draw((*effect));
	}
}

void VisualEffectsHandler::drawTopEffects(sf::RenderWindow & window)
{
	for (auto& effect : topEffectList) {
		window.draw((*effect));
	}
}

void VisualEffectsHandler::addEffect(int effectType, sf::Vector2f pos, float rotation, float speed)
{
	switch (effectType)
	{
	case TRACKTYPE:
	{
		std::unique_ptr<Effect> effect = std::make_unique<Track>(pos, rotation, trackTexture);
		bottomEffectList.push_back(std::move(effect));
		break;
	}
	default:
		break;
	}
}

void VisualEffectsHandler::clearVFX()
{
	bottomEffectList.clear();
	topEffectList.clear();
}
