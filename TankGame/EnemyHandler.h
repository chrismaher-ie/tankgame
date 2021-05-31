#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "UnitTank.h"
#include "BrownTank.h"
#include "Player.h"
#include "BulletHandler.h"

#define BROWNTANKTYPE 1

class EnemyHandler : public sf::Drawable
{
public:
	

	EnemyHandler(Player& playerTank, BulletHandler& bulletHandler);
	~EnemyHandler();
	void update(/*sf::FloatRect boundingBox*/ Player * player);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addEnemy(sf::Vector2f pos, float rotation, int type);
	std::list<UnitTank*> *getTankList();

private:
	std::list<UnitTank*> tankList;
	Player& playerTank;
	BulletHandler& bulletHandler;
};

