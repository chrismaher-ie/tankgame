#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Enemy.h"
#include "BulletHandler.h"

class EnemyHandler
{
public:
	std::list<Enemy> enemyList;

	EnemyHandler();
	~EnemyHandler();
	void update(/*sf::FloatRect boundingBox*/);
	void draw(sf::RenderWindow& window);
	void addEnemy(sf::Vector2f pos, float rotation);
	BulletHandler* getBulletHandler();

private:
	sf::Texture enemyTexture;
	BulletHandler bulletHandler;
};

