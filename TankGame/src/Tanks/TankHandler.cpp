#include "Tanks/TankHandler.h"

TankHandler::TankHandler(ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler, sf::RenderWindow& window)
	:  projectileHandler(projectileHandler), vfxHandler(vfxHandler), window(window)
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

	playerTank->update();

	for (auto& tank : tankList) {
		//update tank
		tank->update();

	}
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
