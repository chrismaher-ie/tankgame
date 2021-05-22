#pragma once
#include <SFML/Graphics.hpp>
#include "BulletHandler.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(sf::Vector2f pos, float rotation, sf::Texture& texture, BulletHandler* handler, int behaviour);
	~Enemy();
	void update(Player * player);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	bool takeDamage();
	bool die();
	float getSize();

private:
	int health = 5;
	float size = 40.0f;
	int behaviour = 0;

	float fireRate = 6.f; //bullets per second
	sf::Clock fireRateClock;
	sf::Time fireInterval = sf::seconds(1 / fireRate);
	sf::Time fireTimeDelta = sf::seconds(0.f);


	BulletHandler* bulletHandler;
	sf::RectangleShape body;

	bool canShoot();
	void shoot();
	float getAngle(sf::Vector2f v1, sf::Vector2f v2);
	float getTargetLeadAngle(Player* player);
};

