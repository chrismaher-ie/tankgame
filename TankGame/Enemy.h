#pragma once
#include <SFML/Graphics.hpp>
#include "BulletHandler.h"

class Enemy
{
public:
	Enemy(sf::Vector2f pos, float rotation, sf::Texture& texture, BulletHandler* handler);
	~Enemy();
	void update();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	float getSize();

private:
	
	float size = 40.0f;

	float fireRate = 6.f; //bullets per second
	sf::Clock fireRateClock;
	sf::Time fireInterval = sf::seconds(1 / fireRate);
	sf::Time fireTimeDelta = sf::seconds(0.f);


	BulletHandler* bulletHandler;
	sf::RectangleShape body;

	bool canShoot();
	void shoot();

};

