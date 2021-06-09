#include "Barrier.h"

Barrier::Barrier(sf::Vector2f pos, float width, float height, bool fragile, sf::Texture & texture)
{
	this->fragile = fragile;
	body = sf::RectangleShape(sf::Vector2f(width, height));
	body.setOrigin(sf::Vector2f(width / 2, height / 2));

	body.setTexture(&texture);

	body.setPosition(pos);
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

sf::RectangleShape Barrier::getBody()
{
	return body;
}
