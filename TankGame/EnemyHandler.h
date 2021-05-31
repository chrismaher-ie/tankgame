#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Enemy.h"
#include "BulletHandler.h"

class EnemyHandler
{
public:
	

	EnemyHandler(BulletHandler& bulletHandler);
	~EnemyHandler();
	void update(/*sf::FloatRect boundingBox*/ Player * player);
	void draw(sf::RenderWindow& window);
	void addEnemy(sf::Vector2f pos);
	void addEnemy(sf::Vector2f pos, float rotation, int behaviour);
	std::list<Enemy>* getEnemyList();

private:
	std::list<Enemy> enemyList;
	sf::Texture enemyTexture;
	BulletHandler& bulletHandler;
};

