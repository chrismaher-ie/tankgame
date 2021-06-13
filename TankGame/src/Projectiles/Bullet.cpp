#include "Projectiles/Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture, VisualEffectsHandler& vfxHandler)
	: Projectile(pos, rotation, tankId, texture, vfxHandler)
{
	float speed = 0.6f;
	float size = 8.0f;
}

Bullet::~Bullet()
{
}