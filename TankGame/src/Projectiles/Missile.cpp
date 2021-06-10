#include "Projectiles/Missile.h"

Missile::Missile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture)
	: Projectile(pos, rotation, tankId, texture)
{
	speed = 1.2f;
	wallBounces = 0;
	body.scale(1.5f, 1.5f);
	size *= 1.5f;
}

Missile::~Missile()
{
	//Explosion effects here?
}