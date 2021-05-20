#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f pos, float rotation, sf::Texture& mapTexture);
	~Bullet();
	void update();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();

private:
	float speed = 0.6f;
	float size = 8.0f;
	sf::RectangleShape body;

};

