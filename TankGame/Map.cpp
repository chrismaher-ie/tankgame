#include "Map.h"

Map::Map()
{
	map = sf::RectangleShape(sf::Vector2f(600.f, 1000.f));
	map.setPosition(0.f, 0.f);
	map.setOrigin(300.0f, 600.0f);
	mapTexture.loadFromFile("Textures/road.jpg");
	map.setTexture(&mapTexture);
	map.setRotation(90);
}

Map::~Map()
{
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(map);
}

sf::FloatRect Map::getBoundingBox()
{
	return map.getGlobalBounds();
}
