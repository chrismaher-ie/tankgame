#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Tanks/UnitTank.h"
#include "Tanks/BrownTank.h"
#include "Tanks/GreyTank.h"
#include "Tanks/GreenTank.h"
#include "Tanks/Player.h"
#include "Projectiles/ProjectileHandler.h"
#include "VisualEffects/VisualEffectsHandler.h"

#define BROWNTANKTYPE 1
#define GREYTANK 2
#define GREENTANK 3

class TankHandler : public sf::Drawable
{
public:
	

	TankHandler(Player& playerTank, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);
	~TankHandler();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addTank(sf::Vector2f pos, float rotation, int type);
	std::list<std::unique_ptr<UnitTank>> *getTankList();

private:
	std::list<std::unique_ptr<UnitTank>> tankList;
	Player& playerTank;
	ProjectileHandler& projectileHandler;
	VisualEffectsHandler& vfxHandler;
};

