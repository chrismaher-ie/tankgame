#include "Map/Barrier.h"

Barrier::Barrier(sf::Vector2f pos, float width, float height, bool fragile, sf::Texture & texture)
{
	this->fragile = fragile;
	body.setTexture(texture);
	body.setOrigin(sf::Vector2f(body.getTexture()->getSize().x * 0.5f, body.getTexture()->getSize().y  * 0.5f));
	body.setPosition(pos);

	body.setScale(sf::Vector2f(width / body.getTexture()->getSize().x, height / body.getTexture()->getSize().y));
}

Barrier::~Barrier()
{
}

void Barrier::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
}

bool Barrier::isFragile()
{
	return fragile;
}

sf::Sprite Barrier::getBody()
{
	return body;
}
