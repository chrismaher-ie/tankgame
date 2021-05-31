#include "BrownTank.h"

BrownTank::BrownTank(sf::Vector2f pos, float rotation, int teamId, Player& player, BulletHandler& bulletHandler)
	: UnitTank(pos, rotation, teamId, bulletHandler), playerTank(player)
{
	body.setFillColor(sf::Color(165, 42, 42, 150));
	turret.setFillColor(sf::Color(165, 42, 42, 150));
}

BrownTank::~BrownTank()
{
}

void BrownTank::move()
{
	return;
}

bool BrownTank::aim()
{
	body.rotate(0.5f);
	float targetAngle = gutils::getAngle(body.getPosition(), playerTank.getPosition());
	float turretAngle = turret.getRotation();
	if (abs(gutils::getAngleDelta(targetAngle, turretAngle) < 2.0f)) {
		return true;
	}
	return false;
}
