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
	void shoot();
	float size = 40.0f;
	BulletHandler* bulletHandler;
	sf::RectangleShape body;

};

