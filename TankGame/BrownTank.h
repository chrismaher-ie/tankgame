#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "UnitTank.h"
#include "Player.h"

class BrownTank : public UnitTank
{
	public:
		BrownTank(sf::Vector2f pos, float rotation, int teamId, Player& player, ProjectileHandler& projectileHandler);
		~BrownTank();
		void die();
	private:
		float rotationSpeed = 0.4f;

		//NOTE: redeclarations of parent variables as below are ignored in parent methods
		// these variables have been set in the constructor
		//float fireRate = 0.2f; //bullets per second


		Player& playerTank;
		void move();
		bool aim();

};

