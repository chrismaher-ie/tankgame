#include "Enemy.h"
static const float M_PI = 3.14159265358979f;


Enemy::Enemy(sf::Vector2f pos, float rotation, sf::Texture & texture, BulletHandler* handler, int behaviour)
{
	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
	bulletHandler = handler;
	this->behaviour = behaviour;
}

Enemy::~Enemy()
{
}

void Enemy::update(Player * player)
{
	switch (behaviour)
	{
	case 0:
		body.rotate(1.f);
		break;
	case 1:
		body.setRotation(getAngle(body.getPosition(), player->getPosition()));
		break;
	case 2:
		body.setRotation(getTargetLeadAngle(player));
		break;
	default:
		break;
	}
	
	

	if (canShoot()) shoot();
}

void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

sf::Vector2f Enemy::getPosition()
{
	return body.getPosition();
}

bool Enemy::takeDamage()
{
	if (--health == 0) {
		return true;
	}
	return false;
}

bool Enemy::die()
{
	return true;

}

float Enemy::getSize()
{
	return size;
}

bool Enemy::canShoot()
{
	fireTimeDelta += fireRateClock.restart();
	if (fireTimeDelta > fireInterval) {
		fireTimeDelta = sf::seconds(0.f);
		return true;
	}
	return false;
}

void Enemy::shoot()
{
	
	float radian_angle = body.getRotation() / 180.f * M_PI;
	sf::Vector2f bulletPos(body.getPosition().x + (size / 2 * std::cosf(radian_angle)), body.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler->addBullet(bulletPos, body.getRotation());
}

float Enemy::getAngle(sf::Vector2f v1, sf::Vector2f v2)
{
	float angle = std::atan2f(v2.y - v1.y, v2.x - v1.x) * 180 / M_PI;
	return angle;
}

float Enemy::getTargetLeadAngle(Player * player)
{
	float worldAngle = getAngle(body.getPosition(), player->getPosition());
	float relativeAngleRadians;
	float bulletSpeedRatio = 2; //make a ratio of bullet speed/ player speed
	float angleDelta = 0;
	float returnAngle = worldAngle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

		relativeAngleRadians = (180 + worldAngle - player->getRotation()) / 180 * M_PI;
		printf("Angle %f\n", relativeAngleRadians);
		angleDelta = std::asin(sinf(relativeAngleRadians) / bulletSpeedRatio) * 180 / M_PI;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		returnAngle += angleDelta;
	}
	// this does not need to be an else if as; if both keys are held 1. the angles will cancel out and 2. the player will not moving
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { // if player
		returnAngle -= angleDelta;
	}

	return returnAngle;
}