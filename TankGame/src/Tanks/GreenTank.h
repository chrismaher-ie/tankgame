#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/GeometryUtils.h"
#include "Tanks/UnitTank.h"
#include "Tanks/Player.h"

class GreenTank :
	public UnitTank
{
public:
	GreenTank(sf::Vector2f pos, float rotation, int teamId, Player& player, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);
	~GreenTank();
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

