#include "Map.h"

Map::Map()
{
	background = sf::RectangleShape(sf::Vector2f(600.f, 1000.f));
	background.setPosition(0.f, 0.f);
	background.setOrigin(300.0f, 600.0f);
	backgroundTexture.loadFromFile("Textures/road.jpg");
	background.setTexture(&backgroundTexture);
	background.setRotation(90);

	wallTexture.loadFromFile("Textures/Tempwall1.png");
	fragileWallTexture.loadFromFile("Textures/Tempwall2.png");

}

Map::~Map()
{
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background);
	for (auto wall : wallList) {
		target.draw(wall);
	}
}

sf::FloatRect Map::getBoundingBox()
{
	return background.getGlobalBounds();
}

void Map::addWall(sf::Vector2f pos, float height, float width, bool fragile)
{
	if (fragile) {
		wallList.push_back(Wall(pos, height, width, fragile, fragileWallTexture));
	}
	else
	{
		wallList.push_back(Wall(pos, height, width, fragile, wallTexture));
	}
}

std::list<Wall>* Map::getWallList()
{
	return &wallList;
}
