#include "Tanks/GreyTank.h"

GreyTank::GreyTank(sf::Vector2f pos, float rotation, int teamId, Player & player, ProjectileHandler & projectileHandler, VisualEffectsHandler& vfxHandler)
	: UnitTank(pos, rotation, teamId, projectileHandler, vfxHandler), playerTank(player)
{
	body.setColor(sf::Color(70, 70, 70));
	turret.setColor(sf::Color(80, 80, 80));
	fireRate = 0.5f;
}

GreyTank::~GreyTank()
{
}

void GreyTank::die()
{
	dead = true;
}

void GreyTank::move()
{
	//TODO: add movement and pathfinding
	return;

}

bool GreyTank::aim()
{
	float angle = gutils::getAngle(turret.getPosition(), playerTank.getPosition());

	float delta = gutils::getAngleDelta(angle, turret.getRotation());

	if (abs(delta) <= rotationSpeed) {
		turret.rotate(delta);
		return true;
	}

	else { //(abs(delta) > rotationSpeed)

		if (delta > 0) {
			turret.rotate(1 * rotationSpeed);
		}
		if (delta < 0) {
			turret.rotate(-1 * rotationSpeed);
		}
	}
	return false;
}
