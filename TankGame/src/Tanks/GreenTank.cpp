#include "Tanks/GreenTank.h"

GreenTank::GreenTank(sf::Vector2f pos, float rotation, int teamId, std::shared_ptr<PlayerTank> playerTank, ProjectileHandler & projectileHandler, VisualEffectsHandler& vfxHandler)
	: UnitTank(pos, rotation, teamId, projectileHandler, vfxHandler), playerTank(playerTank)
{
	body.setColor(sf::Color(0, 128, 0));
	turret.setColor(sf::Color(0, 128, 0));
	fireRate = 0.4f;
	projectileType = MISSILETYPE;
}

GreenTank::~GreenTank()
{
}

void GreenTank::die()
{
	dead = true;
}

void GreenTank::move()
{
	return;
}

bool GreenTank::aim()
{
	float angle = gutils::getTargetLeadAngle
	(
		turret.getPosition(), playerTank->getPosition(), 
		playerTank->getRotation(), playerTank->getSpeed(), Missile::getSpeed()
	);

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
