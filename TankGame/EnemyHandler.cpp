#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(Player& playerTank, BulletHandler& bulletHandler)
	:  playerTank(playerTank), bulletHandler(bulletHandler)
{
}

EnemyHandler::~EnemyHandler()
{
}

void EnemyHandler::update(Player * player)
{
	for (auto tank_itr = tankList.begin(); tank_itr != tankList.end(); ) {
		//update enemy
		(*tank_itr)->update();

		//if enemy is to be destroyed, delete enemy
		if (false) {
			tank_itr = tankList.erase(tank_itr);
		}
		// elseif more checks

		else { //enemy was fine, increment iterator
			++tank_itr;
		}

	}
}

void EnemyHandler::draw(sf::RenderWindow & window)
{
	for (auto tank : tankList) {
		window.draw((*tank));
	}
}

void EnemyHandler::addEnemy(sf::Vector2f pos, float rotation, int type)
{
	UnitTank * tank;
	switch (type)
	{
	case BROWNTANKTYPE :
		tank = new BrownTank(pos, rotation, 1 /*teamId*/, playerTank, bulletHandler);
		tankList.push_back(tank);
		break;
	default:
		break;
	}

}

std::list<UnitTank*>* EnemyHandler::getTankList()
{
	return &tankList;
}
