#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "BulletHandler.h"


class UnitTank : sf::Drawable
{
public:
	UnitTank(sf::Vector2f pos, float rotation, BulletHandler* handler);
	~UnitTank();

	float getSize();
	float getSpeed();
	float getRotation();
	sf::Vector2f getPosition();

	void takeDamage();
	void die();

	void setTarget(UnitTank* target);
	UnitTank* getTarget();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::RenderWindow& window);

protected:
	int _id;
	static int idCount;

	int health = 1;
	float size = 40.0f;
	float speed = 0.3f;
	float turretSpeed = 0.1f;

	float fireRate = 1.f; //bullets per second
	sf::Clock fireRateClock;
	sf::Time fireInterval = sf::seconds(1 / fireRate);
	sf::Time fireTimeDelta = sf::seconds(0.f);

	BulletHandler* bulletHandler;
	UnitTank* target = nullptr;

	sf::RectangleShape body;
	sf::RectangleShape turret;
	sf::Texture bodyTexture;
	sf::Texture turretTexture;

	virtual void move();
	virtual bool aim();
	bool canShoot();
	void shoot();
};
