#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos, float rotation, sf::Texture& texture);
	~Bullet();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	float getSize();
private:
	float speed = 0.6f;
	float size = 8.0f;
	sf::RectangleShape body;

};

