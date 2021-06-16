#include "Projectiles/Bullet.h"

float Bullet::speed = 0.6f;

Bullet::Bullet(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture, VisualEffectsHandler& vfxHandler)
	: Projectile(pos, rotation, tankId, texture, vfxHandler)
{
	Projectile::speed = speed;
	float size = 8.0f;
	body.setScale(sf::Vector2f(0.5f, 0.5f));
}

Bullet::~Bullet()
{
}

float Bullet::getSpeed()
{
	return speed;
}
