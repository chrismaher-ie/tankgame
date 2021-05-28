#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "BulletHandler.h"
#include "UnitTank.h"

class Player : public UnitTank
{
	public:
		Player(sf::Vector2f pos, float rotation, int teamId, BulletHandler& bulletHandler, sf::RenderWindow& window);
		~Player();

		void die();

		void update();

	private:
		int health = 5;
		float maxSpeed = 0.3f;
		
		sf::RenderWindow& window;
		
		void move();
		bool aim();
		void fireMissile();

};

