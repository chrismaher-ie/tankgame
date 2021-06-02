#include "Bullet.h"

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
	float angle = body.getRotation() * gutils::degreesToRads;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::Vector2f Bullet::getPosition()
{
	return body.getPosition();
}

float Bullet::getSize()
{
	return size;
}

bool Bullet::shouldDelete()
{
	return expired;
}

void Bullet::hit()
{
	expired = true;
}
