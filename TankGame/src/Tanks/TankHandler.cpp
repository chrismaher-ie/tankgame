#include "Tanks/TankHandler.h"

TankHandler::TankHandler(ProjectileHandler& projectileHandler, Map& map, VisualEffectsHandler& vfxHandler, sf::RenderWindow& window)
	:  projectileHandler(projectileHandler), map(map), vfxHandler(vfxHandler), window(window)
{
	playerTank = std::make_shared<PlayerTank>(sf::Vector2f(0.0f, 0.0f), 225.f, 0, projectileHandler, vfxHandler, window);

}

TankHandler::~TankHandler()
{
}

void TankHandler::update()
{
	if (!playerTank) {
		//if the player tank does not exist we should not update any tanks
		return;
	}
	//TODO improve collisions

	playerTank->update();
	//playerTank has type std::shared_ptr<PlayerTank>. calling get() returns the raw pointer
	tankWallCollisionCheck(playerTank.get());

	for (auto& tank : tankList) {
		//update tank
		tank->update();
		//tank has type std::unique_ptr<UnitTank>. calling get() returns the raw pointer
		tankWallCollisionCheck(tank.get());
	}


	//TODO add tank tank collisions
	
	//TODO: check if this is ever needed
	tankList.remove_if([&](const std::unique_ptr<UnitTank>& tank) -> bool { return tank->shouldDelete(); });

}

void TankHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//if the player tank does not exist we should not draw it
	if (playerTank) target.draw((*playerTank));

	
	for (auto& tank : tankList) {
		target.draw((*tank));
	}
}

void TankHandler::addTank(sf::Vector2f pos, float rotation, int type)
{
	//TODO: add teamId functionallity or remove teamId
	switch (type)
	{
	case BROWNTANK :
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

std::shared_ptr<PlayerTank> TankHandler::getPlayerTank()
{
	return playerTank;
}

std::list<std::unique_ptr<UnitTank>>* TankHandler::getTankList()
{
	return &tankList;
}

void TankHandler::tankWallCollisionCheck(UnitTank * tank)
{
	for (auto& wall : *map.getWallList()) {
		if (Collision::BoundingBoxTest(tank->getSprite(), wall.getSprite())) {
			tank->rollBack();
			return;
		}
	}
	for (auto& barrier : *map.getBarrierList()) {
		if (Collision::BoundingBoxTest(tank->getSprite(), barrier.getSprite())) {
			tank->rollBack();
			return;
		}
	}
}
