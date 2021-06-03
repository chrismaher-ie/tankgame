#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture)
	: Projectile(pos, rotation, tankId, texture)
{
	float speed = 0.6f;
	float size = 8.0f;
}

Bullet::~Bullet()
{
}