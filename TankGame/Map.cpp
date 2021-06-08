#include "Map.h"

Map::Map()
{
	background = sf::RectangleShape(sf::Vector2f(1000.f, 600.f));
	background.setPosition(0.f, 0.f);
	background.setOrigin(500.0f, 300.0f);
	backgroundTexture.loadFromFile("Textures/road.jpg");
	background.setTexture(&backgroundTexture);

	wallTexture.loadFromFile("Textures/Tempwall1.png");
	fragileWallTexture.loadFromFile("Textures/Tempwall2.png");

	//setup bounding walls
	addWall(sf::Vector2f(0.0f, -310.0f), 1040.f, 20.f, false);
	addWall(sf::Vector2f(-510.0f, 0.0f), 20.f, 640.f, false);
	addWall(sf::Vector2f(0.0f, 310.0f), 1040.f, 20.f, false);
	addWall(sf::Vector2f(510.0f, 0.0f), 20.f, 640.f, false);

	//setup test walls
	addWall(sf::Vector2f(-200.0f, -200.0f), 80.f, 40.f, true);
	addWall(sf::Vector2f(60.0f, -80.0f), 40.f, 40.f, false);

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

void Map::addWall(sf::Vector2f pos, float width, float height, bool fragile)
{
	if (fragile) {
		wallList.push_back(Wall(pos, width, height, fragile, fragileWallTexture));
	}
	else
	{
		wallList.push_back(Wall(pos, width, height, fragile, wallTexture));
	}
}

std::list<Wall>* Map::getWallList()
{
	return &wallList;
}
