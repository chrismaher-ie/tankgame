#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(BulletHandler& bulletHandler)
	: bulletHandler(bulletHandler)
{
	enemyTexture.loadFromFile("Textures/enemy.png");
}

EnemyHandler::~EnemyHandler()
{
}

void EnemyHandler::update(Player * player)
{
	for (auto enemy_itr = enemyList.begin(); enemy_itr != enemyList.end(); ) {
		//update enemy
		enemy_itr->update(player);

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

void EnemyHandler::addEnemy(sf::Vector2f pos)
{
	Enemy enemy = Enemy(pos, 0.f, enemyTexture, bulletHandler, 0);
	enemyList.push_back(enemy);
}

void EnemyHandler::addEnemy(sf::Vector2f pos, float rotation, int behaviour)
{
	Enemy enemy = Enemy(pos, rotation, enemyTexture, bulletHandler, behaviour);
	enemyList.push_back(enemy);
}

std::list<Enemy>* EnemyHandler::getEnemyList()
{
	return &enemyList;
}
