#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "UnitTank.h"
#include "Player.h"

class BrownTank : public UnitTank
{
	public:
		BrownTank(sf::Vector2f pos, float rotation, int teamId, Player& player, BulletHandler& bulletHandler);
		~BrownTank();

	private:

		float fireRate = 0.2f; //bullets per second
		Player& playerTank;
		void move();
		bool aim();

};

