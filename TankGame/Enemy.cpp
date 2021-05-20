#include "Enemy.h"
static const float M_PI = 3.14159265358979f;


Enemy::Enemy(sf::Vector2f pos, float rotation, sf::Texture & texture, BulletHandler* handler)
{
	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
	bulletHandler = handler;
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	body.rotate(1.f);
	shoot();
}

void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

sf::Vector2f Enemy::getPosition()
{
	return body.getPosition();
}

float Enemy::getSize()
{
	return size;
}

void Enemy::shoot()
{
	
	float radian_angle = body.getRotation() / 180.f * M_PI;
	sf::Vector2f bulletPos(body.getPosition().x + (size / 2 * std::cosf(radian_angle)), body.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler->addBullet(bulletPos, body.getRotation());
}
