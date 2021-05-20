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

	private:
		float speed = 0.3f;
		float size = 40.0f;
		sf::RectangleShape body;
		sf::RectangleShape turret;
		sf::Texture bodyTexture;
		sf::Texture turretTexture;
		BulletHandler bulletHandler;

		void shoot();
		void moveForward();
		void moveBackward();
		float getAngle(sf::Vector2f v1, sf::Vector2f v2);
};

