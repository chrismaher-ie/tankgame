#include "Tanks/UnitTank.h"

int UnitTank::idCount = 0;


UnitTank::UnitTank(sf::Vector2f pos, float rotation, int teamId, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler)
	: projectileHandler(projectileHandler), vfxHandler(vfxHandler)
{
	_id = idCount;
	idCount++;
	this->teamId = teamId;

	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));

	bodyTexture.loadFromFile("Assets/Textures/tankBase.png");
	body.setTexture(&bodyTexture);

	turret = sf::RectangleShape(sf::Vector2f(size, size));
	turret.setOrigin(sf::Vector2f(size / 2, size / 2));
	

	turretTexture.loadFromFile("Assets/Textures/tankTurret.png");
	turret.setTexture(&turretTexture);

	body.setPosition(pos);
	body.setRotation(rotation);

	turret.setPosition(pos);
	turret.setRotation(rotation);

}

UnitTank::~UnitTank()
{
}

int UnitTank::getTeam()
{
	return teamId;
}

int UnitTank::getHealth()
{
	return health;
}

float UnitTank::getSize()
{
	return size;
}

float UnitTank::getSpeed()
{
	return currentSpeed;
}

float UnitTank::getRotation()
{
	return body.getRotation();
}

sf::Vector2f UnitTank::getPosition()
{
	return body.getPosition();
}

void UnitTank::takeDamage()
{
	if (--health <= 0) {
		die();
	}
}

void UnitTank::die()
{
	//to be implemented in child classes
	return;
}

bool UnitTank::shouldDelete()
{
	return dead;
}

void UnitTank::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
	target.draw(turret);
}

void UnitTank::update()
{
	//Movement 
	move();
	if (currentSpeed != 0.0f) {
		if (++trackEffectSpawnCounter > trackEffectSpawnInterval) {
			trackEffectSpawnCounter = 0;
			vfxHandler.addEffect(TRACKTYPE, body.getPosition(), body.getRotation());
		}
	}
	turret.setPosition(body.getPosition());

	//Shooting
	if (aim()) {
		if (canShoot()) {
			shoot(projectileType);
		}
	}
}

void UnitTank::move()
{
	//move determined by behaviour
	//virtual function to be implemented by child classes
	return;
}

bool UnitTank::aim()
{
	//angle to target and return true if pointing at target
	//virtual function to be implemented by child classes
	return false;
}

bool UnitTank::canShoot()
{
	if (projectileHandler.countTankProjectiles(_id) < maxProjectiles) {

		fireTimeDelta += fireRateClock.restart();
		if (fireTimeDelta > fireInterval) {
			fireTimeDelta = sf::seconds(0.f);
			return true;
		}
	}
	return false;
}

void UnitTank::shoot(int projectileType)
{
	//TODO: tune bullet spawn position so it doesn't instantly collide with origin tank
	float radian_angle = turret.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(turret.getPosition().x + (size * std::cosf(radian_angle)), turret.getPosition().y + (size * std::sinf(radian_angle)));
	projectileHandler.addProjectile(bulletPos, turret.getRotation(), projectileType, _id);
}