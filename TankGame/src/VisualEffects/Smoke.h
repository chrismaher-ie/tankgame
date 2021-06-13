#pragma once
#include <SFML/Graphics.hpp>
#include "VisualEffects/Effect.h"
#include "Utils/GeometryUtils.h"

class Smoke : public Effect
{
public:
	Smoke(sf::Vector2f pos, float rotation, float speed, sf::Texture& texture);
	~Smoke();

	void update();

private:
	float width = 10.f;
	float heigth = 10.f;
	float angle;
	float speed;

	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time expireTime = sf::seconds(1);
};