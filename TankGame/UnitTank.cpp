#include "UnitTank.h"

int UnitTank::idCount = 0;


UnitTank::UnitTank(sf::Vector2f pos, float rotation, BulletHandler* bullethandler)
{
	_id = idCount;
	idCount++;


	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));

	bodyTexture.loadFromFile("Textures/tankBase.png");
	body.setTexture(&bodyTexture);

	turret = sf::RectangleShape(sf::Vector2f(size, size));
	turret.setOrigin(sf::Vector2f(size / 2, size / 2));
	

	turretTexture.loadFromFile("Textures/tankTurret.png");
	turret.setTexture(&turretTexture);

	body.setPosition(pos);
	body.setRotation(rotation);

	turret.setPosition(pos);
	turret.setRotation(rotation);

	this->bulletHandler = bulletHandler;


}

UnitTank::~UnitTank()
{
}

float UnitTank::getSize()
{
	return size;
}

float UnitTank::getSpeed()
{
	return speed;
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
	//delete this unit
	//maybe add id into death list
}

void UnitTank::setTarget(UnitTank * target)
{
	this->target = target;
}

UnitTank * UnitTank::getTarget()
{
	return target;
}

void UnitTank::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
	target.draw(turret);
}

void UnitTank::update(sf::RenderWindow & window)
{
	//Movement 
	move();

	//Shooting
	if (aim()) {
		if (canShoot()) {
			shoot();
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
	fireTimeDelta += fireRateClock.restart();
	if (fireTimeDelta > fireInterval) {
		fireTimeDelta = sf::seconds(0.f);
		return true;
	}
	return false;
}

void UnitTank::shoot()
{
	//Move code to bulletHandler->addBullet()
	float radian_angle = body.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(body.getPosition().x + (size / 2 * std::cosf(radian_angle)), body.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler->addBullet(bulletPos, body.getRotation());
}
