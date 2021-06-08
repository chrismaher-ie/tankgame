#include "Wall.h"

Wall::Wall(sf::Vector2f pos, float height, float width, bool fragile, sf::Texture& texture)
{
	this->fragile = fragile;
	body = sf::RectangleShape(sf::Vector2f(height, width));
	body.setOrigin(sf::Vector2f(height / 2, width / 2));

	body.setTexture(&texture);

	body.setPosition(pos);
}

Wall::~Wall()
{

}

void Wall::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
}

bool Wall::isFragile()
{
	return fragile;
}

sf::RectangleShape Wall::getBody()
{
	return body;
}

