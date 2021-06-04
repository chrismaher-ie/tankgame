#include "EnemyHandler.h"

EnemyHandler::EnemyHandler(Player& playerTank, ProjectileHandler& projectileHandler)
	:  playerTank(playerTank), projectileHandler(projectileHandler)
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

void EnemyHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto tank : tankList) {
		target.draw((*tank));
	}
}

void EnemyHandler::addEnemy(sf::Vector2f pos, float rotation, int type)
{
	//TODO: add teamId functionallity or remove teamId
	UnitTank * tank;
	switch (type)
	{
	case BROWNTANKTYPE :
		tank = new BrownTank(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler);
		tankList.push_back(tank);
		break;

	case GREYTANK:
		tank = new GreyTank(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler);
		tankList.push_back(tank);
		break;

	case GREENTANK:
		tank = new GreenTank(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler);
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
