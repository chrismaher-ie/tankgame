#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"

//Todo, inherit from projectile class
class Missile : public sf::Drawable
{
public:
	

	Missile(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture);
	~Missile();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f getPosition();
	float getSize();
	bool shouldDelete();
	void hit();
	int getTankId();

private:
	float speed = 1.2f;
	float turnSpeed = 0.5f;
	float size = 16.0f;
	sf::Clock lifeTimeclock;
	sf::Time lifeTime = sf::seconds(3.f);

	int tankId;
	bool expired = false;

	sf::RectangleShape body;


	sf::Vector2f getMousPos(sf::RenderWindow& window);
	void moveToTarget(sf::Vector2f targetPos);

};

