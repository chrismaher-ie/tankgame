#include "Enemy.h"

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
	//TODO access Bullet bulletSpeed
	float bulletSpeed = 0.6f;
	switch (behaviour)
	{
	case 0:
		body.rotate(1.f);
		break;
	case 1:
		body.setRotation(gutils::getAngle(body.getPosition(), player->getPosition()));
		break;
	case 2:
		body.setRotation(gutils::getTargetLeadAngle(
			body.getPosition(), player->getPosition(), player->getRotation(), player->getSpeed(), bulletSpeed
		));
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
	
	float radian_angle = body.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(body.getPosition().x + (size / 2 * std::cosf(radian_angle)), body.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler->addBullet(bulletPos, body.getRotation());
}