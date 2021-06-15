#pragma once
#include <SFML/Graphics.hpp>
#include "VisualEffects/Effect.h"

class Track : public Effect
{
public:
	Track(sf::Vector2f pos, float rotation, sf::Texture& texture);
	~Track();

	void update();

private:

	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time expireTime = sf::seconds(5);
};