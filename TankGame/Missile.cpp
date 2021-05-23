#include "Missile.h"
static const float M_PI = 3.14159265358979f;

Missile::Missile(sf::Vector2f pos, float rotation, sf::Texture& texture)
{
	body = sf::RectangleShape(sf::Vector2f(size, size/2));
	body.setOrigin(sf::Vector2f(size / 2, size / 4));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);
	lifeTimeclock.restart();
}

Missile::~Missile()
{
}


// move explosion logic elsewhere
void Missile::update(sf::RenderWindow& window)
{
	if (lifeTimeclock.getElapsedTime() > lifeTime) {
		expired = true;
	}
	//TODO: make tracking speed slower
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float angle = std::atan2f(mouseWorldPos.y - body.getPosition().y, mouseWorldPos.x - body.getPosition().x);
	body.setRotation(angle * 180 / M_PI);
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Missile::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

sf::Vector2f Missile::getPosition()
{
	return body.getPosition();
}

float Missile::getSize()
{
	return size;
}
