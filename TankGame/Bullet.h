#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"

//Todo inherit from projectile class
class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture);
	~Bullet();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	float getSize();
	bool shouldDelete();
	void hit();
	int getTankId();

private:
	float speed = 0.6f;
	float size = 8.0f;

	int tankId;
	bool expired = false;

	sf::RectangleShape body;

};

