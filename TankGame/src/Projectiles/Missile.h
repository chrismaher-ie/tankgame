#pragma once
#include <SFML/Graphics.hpp>
#include "Projectiles/Projectile.h"

//Todo, inherit from projectile class
class Missile : public Projectile
{
public:
	Missile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture, VisualEffectsHandler& vfxHandler);
	~Missile();
private:
	//NOTE: redeclarations of parent variables as below are ignored in parent methods
	// these variables have been set in the constructor
	//float speed = 1.2f;
	//int wallBounces = 0;

	int trailEffectSpawnCounter = 0;
	int trailEffectSpawnInterval = 8;

	void spawnTrail();
};