#include "Tanks/EnemyHandler.h"

EnemyHandler::EnemyHandler(Player& playerTank, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler)
	:  playerTank(playerTank), projectileHandler(projectileHandler), vfxHandler(vfxHandler)
{
}

EnemyHandler::~EnemyHandler()
{
}

void EnemyHandler::update(Player * player)
{
	//TODO: remove erase from loop and change to range based loop
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
	for (auto& tank : tankList) {
		target.draw((*tank));
	}
}

void EnemyHandler::addEnemy(sf::Vector2f pos, float rotation, int type)
{
	//TODO: add teamId functionallity or remove teamId
	switch (type)
	{
	case BROWNTANKTYPE :
	{
		std::unique_ptr<UnitTank> tank = std::make_unique<BrownTank>(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler, vfxHandler);
		tankList.push_back(std::move(tank));
		break;
	}
	case GREYTANK:
	{
		std::unique_ptr<UnitTank> tank = std::make_unique<GreyTank>(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler, vfxHandler);
		tankList.push_back(std::move(tank));
		break;
	}
	case GREENTANK:
	{
		std::unique_ptr<UnitTank> tank = std::make_unique<GreenTank>(pos, rotation, 1 /*teamId*/, playerTank, projectileHandler, vfxHandler);
		tankList.push_back(std::move(tank));
		break;
	}
	default:
		break;
	}

}

std::list<std::unique_ptr<UnitTank>>* EnemyHandler::getTankList()
{
	return &tankList;
}
