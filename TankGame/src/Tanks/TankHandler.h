#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Tanks/UnitTank.h"
#include "Tanks/BrownTank.h"
#include "Tanks/GreyTank.h"
#include "Tanks/GreenTank.h"
#include "Tanks/PlayerTank.h"
#include "Projectiles/ProjectileHandler.h"
#include "VisualEffects/VisualEffectsHandler.h"
#include "Map/Map.h"
#include "Collision.h"

#define PLAYERTANK 0
#define BROWNTANK 1
#define GREYTANK 2
#define GREENTANK 3

class TankHandler : public sf::Drawable
{
public:
	

	TankHandler(ProjectileHandler& projectileHandler, Map& map, VisualEffectsHandler& vfxHandler, sf::RenderWindow& window);
	~TankHandler();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addTank(sf::Vector2f pos, float rotation, int type);
	std::shared_ptr<PlayerTank> getPlayerTank();
	std::list<std::unique_ptr<UnitTank>> *getTankList();

private:
	std::shared_ptr<PlayerTank> playerTank;

	std::list<std::unique_ptr<UnitTank>> tankList;
	
	ProjectileHandler& projectileHandler;
	Map& map;
	VisualEffectsHandler& vfxHandler;
	sf::RenderWindow& window;

	void tankWallCollisionCheck(UnitTank *tank);
};

