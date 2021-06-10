#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Tanks/UnitTank.h"
#include "Tanks/BrownTank.h"
#include "Tanks/GreyTank.h"
#include "Tanks/GreenTank.h"
#include "Tanks/Player.h"
#include "Projectiles/ProjectileHandler.h"

#define BROWNTANKTYPE 1
#define GREYTANK 2
#define GREENTANK 3

class EnemyHandler : public sf::Drawable
{
public:
	

	EnemyHandler(Player& playerTank, ProjectileHandler& projectileHandler);
	~EnemyHandler();
	void update(/*sf::FloatRect boundingBox*/ Player * player);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addEnemy(sf::Vector2f pos, float rotation, int type);
	std::list<std::unique_ptr<UnitTank>> *getTankList();

private:
	std::list<std::unique_ptr<UnitTank>> tankList;
	Player& playerTank;
	ProjectileHandler& projectileHandler;
};

