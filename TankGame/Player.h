#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "ProjectileHandler.h"
#include "UnitTank.h"

class Player : public UnitTank
{
	public:
		Player(sf::Vector2f pos, float rotation, int teamId, ProjectileHandler& projectileHandler, sf::RenderWindow& window);
		~Player();

		void die();

		void update();

	private:

		//NOTE: redeclarations of parent variables as below are ignored in parent methods
		// these variables have been set in the constructor
		//int health = 5;
		//float maxSpeed = 0.3f;
		//int maxProjectiles = 3;
		//float fireRate = 5.f;

		sf::RenderWindow& window;
		
		void move();
		bool aim();

};

