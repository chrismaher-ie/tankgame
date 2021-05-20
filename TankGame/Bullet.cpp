#include "Bullet.h"
static const float M_PI = 3.14159265358979f;

Bullet::Bullet(sf::Vector2f pos, float rotation, sf::Texture& texture)
{
	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	float angle = body.getRotation() / 180.f * M_PI;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Bullet::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

sf::Vector2f Bullet::getPosition()
{
	return body.getPosition();
}

float Bullet::getSize()
{
	return size;
}
