#pragma once
#include <SFML/Graphics.hpp>
#include "BulletHandler.h"


class Player
{
	public:
		Player();
		~Player();
		void update(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);
		sf::Vector2f getPosition();
		BulletHandler* getBulletHandler();
		float getRotation();
		void takeDamage();
		void die();
		float getSize();

	private:
		int health = 5;
		float speed = 0.3f;
		float size = 40.0f;

		float fireRate = 1.f; //bullets per second
		sf::Clock fireRateClock;
		sf::Time fireInterval = sf::seconds(1 / fireRate);
		sf::Time fireTimeDelta = sf::seconds(0.f);

		sf::RectangleShape body;
		sf::RectangleShape turret;
		sf::Texture bodyTexture;
		sf::Texture turretTexture;
		BulletHandler bulletHandler;

		
		bool canShoot();
		void shoot();
		void moveForward();
		void moveBackward();
		float getAngle(sf::Vector2f v1, sf::Vector2f v2);
};

