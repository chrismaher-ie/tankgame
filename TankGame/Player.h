#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player();
		~Player();
		void update(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);
		sf::Vector2f getPosition();

	private:
		float speed = 0.05f;
		float size = 40.0f;
		sf::RectangleShape body;
		sf::RectangleShape turret;
		sf::Texture bodyTexture;
		sf::Texture turretTexture;

		void moveForward();
		void moveBackward();
		float getAngle(sf::Vector2f v1, sf::Vector2f v2);
};

