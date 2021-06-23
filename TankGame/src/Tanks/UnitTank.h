#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/GeometryUtils.h"
#include "Projectiles/ProjectileHandler.h"
#include "VisualEffects/VisualEffectsHandler.h"

class UnitTank : public sf::Drawable
{
public:
	UnitTank(sf::Vector2f pos, float rotation, int teamId, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler);
	virtual ~UnitTank();

	int getTeam();
	int getHealth();
	float getSize();
	float getSpeed();
	float getRotation();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();

	void takeDamage();
	virtual void die();
	bool shouldDelete();
	void rollBack();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();

protected:
	int _id;
	static int idCount;

	int teamId;
	int health = 1;
	bool dead = false;
	float size = 40.0f;
	float maxSpeed = 0.3f;
	float currentSpeed = 0.0f;
	float turretSpeed = 0.1f;

	float previousRotation;
	sf::Vector2f previousPosition;
	
	int projectileType = BULLETTYPE;
	int maxProjectiles = 1;
	float fireRate = 1.f; //bullets per second
	sf::Clock fireRateClock;
	sf::Time fireInterval = sf::seconds(1 / fireRate);
	sf::Time fireTimeDelta = fireInterval; //initialise the fireTimeDelta so that tanks dont wait for the first shot

	int trackEffectSpawnCounter = 0;
	int trackEffectSpawnInterval = 20;

	ProjectileHandler& projectileHandler;
	VisualEffectsHandler& vfxHandler;

	sf::Sprite body;
	sf::Sprite turret;
	sf::Texture bodyTexture;
	sf::Texture turretTexture;

	virtual void move();
	virtual bool aim();
	bool canShoot();
	void shoot(int projectileType);
};

