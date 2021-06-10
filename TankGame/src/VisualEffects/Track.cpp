#include "Track.h"

Track::Track(sf::Vector2f pos, float rotation, sf::Texture& texture)
{
	body = sf::RectangleShape(sf::Vector2f(heigth, width));
	body.setOrigin(sf::Vector2f(heigth / 2, width / 2));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
}

Track::~Track()
{
}

void Track::update()
{
	elapsedTime += clock.restart();
	if (elapsedTime > expireTime) {
		expired = true;
	}
}
