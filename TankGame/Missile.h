#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"

class Missile : public sf::Drawable
{
public:
	bool expired = false;

	Missile(sf::Vector2f pos, float rotation, sf::Texture& texture);
	~Missile();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	float getSize();
private:
	float speed = 1.2f;
	float turnSpeed = 0.5f;
	float size = 16.0f;
	sf::Vector2f getMousPos(sf::RenderWindow& window);
	void moveToTarget(sf::Vector2f targetPos);
	sf::RectangleShape body;
	sf::Clock lifeTimeclock;
	sf::Time lifeTime = sf::seconds(3.f);
};

