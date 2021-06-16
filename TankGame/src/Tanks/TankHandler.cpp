#include "Tanks/TankHandler.h"

TankHandler::TankHandler(Player& playerTank, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler)
	:  playerTank(playerTank), projectileHandler(projectileHandler), vfxHandler(vfxHandler)
{
}

TankHandler::~TankHandler()
{
}

void TankHandler::update()
{
	for (auto& tank : tankList) {
		//update tank
		tank->update();

	}
	tankList.remove_if([&](const std::unique_ptr<UnitTank>& tank) -> bool { return tank->shouldDelete(); });

}

void TankHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& tank : tankList) {
		target.draw((*tank));
	}
}

void TankHandler::addTank(sf::Vector2f pos, float rotation, int type)
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

std::list<std::unique_ptr<UnitTank>>* TankHandler::getTankList()
{
	return &tankList;
}
