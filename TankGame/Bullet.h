#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f pos, float rotation, sf::Texture& mapTexture);
	~Bullet();
	void update();
	void draw(sf::RenderWindow& window);

private:
	float speed = 0.3f;
	float size = 19.0f;
	sf::RectangleShape body;

};

