#include "Map.h"

Map::Map()
{
	map = sf::RectangleShape(sf::Vector2f(1200.f, 2000.f));
	map.setPosition(0.f, 0.f);
	map.setOrigin(600.0f, 1200.0f);
	mapTexture.loadFromFile("Textures/road.jpg");
	map.setTexture(&mapTexture);
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow & window)
{
	window.draw(map);
}

sf::FloatRect Map::getBoundingBox()
{
	return map.getGlobalBounds();
}
