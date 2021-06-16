#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/GeometryUtils.h"
#include "Tanks/UnitTank.h"
#include "Tanks/PlayerTank.h"

class GreyTank :
	public UnitTank
{
public:
	GreyTank(sf::Vector2f pos, float rotation, int teamId, PlayerTank& playerTank, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);
	~GreyTank();
	void die();
private:
	float rotationSpeed = 0.4f;

	//NOTE: redeclarations of parent variables as below are ignored in parent methods
	// these variables have been set in the constructor
	//float fireRate = 0.5f; //bullets per second


	PlayerTank& playerTank;
	void move();
	bool aim();
};

