#include "EnemyHandler.h"

EnemyHandler::EnemyHandler()
{
	enemyTexture.loadFromFile("Textures/enemy.png");
}

EnemyHandler::~EnemyHandler()
{
}

void EnemyHandler::update()
{
	for (auto enemy_itr = enemyList.begin(); enemy_itr != enemyList.end(); ) {
		//update enemy
		(*enemy_itr).update();

		//if enemy is to be destroyed, delete enemy
		if (false) {
			enemy_itr = enemyList.erase(enemy_itr);
		}
		// elseif more checks

		else { //enemy was fine, increment iterator
			++enemy_itr;
		}

	}
}

void EnemyHandler::draw(sf::RenderWindow & window)
{
	for (auto& enemy : enemyList) {
		enemy.draw(window);
	}
}

void EnemyHandler::addEnemy(sf::Vector2f pos, float rotation)
{
	Enemy enemy = Enemy(pos, rotation, enemyTexture, &bulletHandler);
	enemyList.push_back(enemy);
}

BulletHandler * EnemyHandler::getBulletHandler()
{
	return &bulletHandler;
}

std::list<Enemy>* EnemyHandler::getEnemyList()
{
	return &enemyList;
}
