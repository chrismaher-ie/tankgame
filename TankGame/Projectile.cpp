#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, float rotation, int tankId, sf::Texture & texture)
{
	body = sf::RectangleShape(sf::Vector2f(size, size / 2));
	body.setOrigin(sf::Vector2f(size / 2, size / 4));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
	this->tankId = tankId;
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	float angle = body.getRotation() * gutils::degreesToRads;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::Vector2f Projectile::getPosition()
{
	return body.getPosition();
}

float Projectile::getSize()
{
	return size;
}

bool Projectile::shouldDelete()
{
	return expired;
}

void Projectile::hit()
{
	expired = true;
}

void Projectile::wallHit()
{
	if (wallBounces > 0) {
		--wallBounces;
		//TODO:
		//reflect bullet off wall
	}
	else {
		expired = true;
	}
}

int Projectile::getTankId()
{
	return tankId;
}
