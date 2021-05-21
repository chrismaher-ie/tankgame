#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Enemy.h"
#include "BulletHandler.h"

class EnemyHandler
{
public:
	

	EnemyHandler();
	~EnemyHandler();
	void update(/*sf::FloatRect boundingBox*/);
	void draw(sf::RenderWindow& window);
	void addEnemy(sf::Vector2f pos, float rotation);
	BulletHandler* getBulletHandler();
	std::list<Enemy>* getEnemyList();

private:
	std::list<Enemy> enemyList;
	sf::Texture enemyTexture;
	BulletHandler bulletHandler;
};

