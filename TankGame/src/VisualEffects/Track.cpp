#include "Track.h"

Track::Track(sf::Vector2f pos, float rotation, sf::Texture& texture)
{
	body.setTexture(texture);
	body.setOrigin(sf::Vector2f(body.getTexture()->getSize().x * 0.5f, body.getTexture()->getSize().y  * 0.5f));
	body.setPosition(pos);
	body.setRotation(rotation);
	
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
