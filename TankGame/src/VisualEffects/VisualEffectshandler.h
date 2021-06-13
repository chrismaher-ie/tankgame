#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "VisualEffects/Effect.h"
#include "VisualEffects/Track.h"
#include "VisualEffects/Smoke.h"


#define TRACKTYPE 1
#define SMOKETYPE 2

class VisualEffectsHandler
{
public:

	VisualEffectsHandler();
	~VisualEffectsHandler();

	void update();
	void drawBottomEffects(sf::RenderWindow& window);
	void drawTopEffects(sf::RenderWindow& window);
	void addEffect(int effectType, sf::Vector2f pos, float rotation = 0, float speed = 0);
	void clearVFX();
private:
	std::list<std::unique_ptr<Effect>> bottomEffectList;
	std::list<std::unique_ptr<Effect>> topEffectList;

	//Textures
	sf::Texture trackTexture;
	sf::Texture smokeTexture;
};

