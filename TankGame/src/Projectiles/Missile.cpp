#include "Projectiles/Missile.h"

Missile::Missile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture, VisualEffectsHandler& vfxHandler)
	: Projectile(pos, rotation, tankId, texture, vfxHandler)
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

void Missile::spawnTrail()
{
	if (++trailEffectSpawnCounter > trailEffectSpawnInterval) {
		trailEffectSpawnCounter = 0;
		vfxHandler.addEffect(SMOKETYPE, body.getPosition(), body.getRotation(),0.2f);
	}
}
