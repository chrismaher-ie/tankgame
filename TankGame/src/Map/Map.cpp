#include "Map/Map.h"

Map::Map()
{
	//Setup background Srite
	backgroundTexture.loadFromFile("Assets/Textures/road.jpg");
	background.setTexture(backgroundTexture);
	background.setPosition(0.f, 0.f);
	background.setOrigin(sf::Vector2f(background.getTexture()->getSize().x * 0.5f, background.getTexture()->getSize().y  * 0.5f));
	background.setScale(sf::Vector2f(1000.f / background.getTexture()->getSize().x, 600.f / background.getTexture()->getSize().y));

	wallTexture.loadFromFile("Assets/Textures/Tempwall1.png");
	fragileWallTexture.loadFromFile("Assets/Textures/Tempwall2.png");

	barrierTexture.loadFromFile("Assets/Textures/Tempbarrier1.png");
	fragileBarrierTexture.loadFromFile("Assets/Textures/Tempbarrier2.png");

	//setup bounding walls
	addWall(sf::Vector2f(0.0f, -310.0f), 1040.f, 20.f, false);
	addWall(sf::Vector2f(-510.0f, 0.0f), 20.f, 640.f, false);
	addWall(sf::Vector2f(0.0f, 310.0f), 1040.f, 20.f, false);
	addWall(sf::Vector2f(510.0f, 0.0f), 20.f, 640.f, false);

	//setup test walls
	addWall(sf::Vector2f(-200.0f, -200.0f), 40.f, 40.f, true);
	addWall(sf::Vector2f(60.0f, -80.0f), 40.f, 40.f, false);

	//Add test barriers
	addBarrier(sf::Vector2f(-250.0f, -200.0f), 40.f, 40.f, true);
	addBarrier(sf::Vector2f(60.0f, 80.0f), 40.f, 40.f, false);

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
	for (auto barrier : barrierList) {
		target.draw(barrier);
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

void Map::addBarrier(sf::Vector2f pos, float height, float width, bool fragile)
{
	if (fragile) {
		barrierList.push_back(Barrier(pos, width, height, fragile, fragileBarrierTexture));
	}
	else
	{
		barrierList.push_back(Barrier(pos, width, height, fragile, barrierTexture));
	}
}

std::list<Wall>* Map::getWallList()
{
	return &wallList;
}

std::list<Barrier>* Map::getBarrierList()
{
	return &barrierList;
}
