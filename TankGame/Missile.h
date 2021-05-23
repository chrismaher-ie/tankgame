#pragma once
#include <SFML/Graphics.hpp>

class Missile
{
public:
	bool expired = false;

	Missile(sf::Vector2f pos, float rotation, sf::Texture& texture);
	~Missile();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	float getSize();
private:
	float speed = 1.2f;
	float size = 16.0f;
	
	sf::RectangleShape body;
	sf::Clock lifeTimeclock;
	sf::Time lifeTime = sf::seconds(3.f);
};

