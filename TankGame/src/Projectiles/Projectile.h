#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/GeometryUtils.h"

class Projectile : public sf::Drawable
{
public:
	Projectile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture);
	virtual ~Projectile();
	virtual void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	float getSize();
	bool shouldDelete();
	void hit();
	void wallHit();
	int getTankId();

protected:
	float speed = 0.6f;
	float size = 8.0f;

	int tankId;
	int wallBounces = 1;
	bool expired = false;

	sf::RectangleShape body;
};

