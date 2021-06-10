#include "Tanks/BrownTank.h"

BrownTank::BrownTank(sf::Vector2f pos, float rotation, int teamId, Player& player, ProjectileHandler& projectileHandler)
	: UnitTank(pos, rotation, teamId, projectileHandler), playerTank(player)
{
	body.setFillColor(sf::Color(165, 42, 42));
	turret.setFillColor(sf::Color(165, 42, 42));
	fireRate = 0.2f;
}

BrownTank::~BrownTank()
{
}

void BrownTank::die()
{
	dead = true;
}

void BrownTank::move()
{
	return;
}

bool BrownTank::aim()
{
	turret.rotate(rotationSpeed);
	float targetAngle = gutils::getAngle(turret.getPosition(), playerTank.getPosition());
	float turretAngle = turret.getRotation();
	if (abs(gutils::getAngleDelta(targetAngle, turretAngle)) < rotationSpeed) {
		return true;
	}
	return false;
}
