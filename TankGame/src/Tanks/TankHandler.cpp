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

	//check tank to tank collisions
	for (auto tank_itr1 = tankList.begin(); tank_itr1 != tankList.end(); ++tank_itr1) {
		
		tankTankCollisionCheck(tank_itr1->get(), playerTank.get());
		//nested loop over single tankList, no repeated checks or self comparision checks
		for (auto tank_itr2 = std::next(tank_itr1, 1); tank_itr2 != tankList.end(); ++tank_itr2) {
			tankTankCollisionCheck(tank_itr1->get(), tank_itr2->get());

			//NOTE: this can cause wall sandwhiching if multiple collisions happen to the sametank
			// as each tank->push() resets the rollback position
			tankTankCollisionCheck(tank_itr1->get(), tank_itr2->get());
		}
	}

	tankWallCollisionCheck(playerTank.get());

	for (auto& tank : tankList) {

		tankWallCollisionCheck(tank.get());
	}
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

void TankHandler::tankTankCollisionCheck(UnitTank * tank1, UnitTank * tank2)
{
	float tankSize = 20.f; //TODO: make dynamic
	float deltaX, deltaY;

	if (Collision::BoundingBoxTest(tank1->getSprite(), tank2->getSprite())) {
		sf::Vector2f dist = tank1->getPosition() - tank2->getPosition();
		float scaler = (2 * tankSize) / std::hypotf(dist.x, dist.y);
		if (scaler <= 1.f) {
			return;
		}
		//TODO: scale scale by relative rotations between 1.0f and 1.12f

		sf::Vector2f idealDist = dist * scaler;
		sf::Vector2f delta = idealDist - dist;

		tank1->push(delta.x, delta.y);
		tank2->push(-delta.x, -delta.y);
	}
}
