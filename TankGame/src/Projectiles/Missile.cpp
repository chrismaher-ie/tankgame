#include "Projectiles/Missile.h"

float Missile::speed = 1.2f;

Missile::Missile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture, VisualEffectsHandler& vfxHandler)
	: Projectile(pos, rotation, tankId, texture, vfxHandler)
{
	Projectile::speed = speed;
	wallBounces = 0;
	body.setScale(sf::Vector2f(0.5f, 0.5f));
	size *= 1.5f;
}

Missile::~Missile()
{
	//Explosion effects here?
}

float Missile::getSpeed()
{
	return speed;
}

void Missile::spawnTrail()
{
	if (++trailEffectSpawnCounter > trailEffectSpawnInterval) {
		trailEffectSpawnCounter = 0;
		vfxHandler.addEffect(SMOKETYPE, body.getPosition(), body.getRotation(),0.2f);
	}
}
