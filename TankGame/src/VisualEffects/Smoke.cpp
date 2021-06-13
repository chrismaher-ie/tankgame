#include "Smoke.h"

Smoke::Smoke(sf::Vector2f pos, float rotation, float speed, sf::Texture& texture)
{
	body = sf::RectangleShape(sf::Vector2f(heigth, width));
	body.setOrigin(sf::Vector2f(heigth / 2, width / 2));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.setTexture(&texture);

	angle = rotation * gutils::degreesToRads;
	this->speed = speed;
}

Smoke::~Smoke()
{
}

void Smoke::update()
{
	elapsedTime += clock.restart();
	if (elapsedTime > expireTime) {
		expired = true;
	}

	body.rotate(3.f);
	int alphaChannel = static_cast<int>(255 * (expireTime - elapsedTime).asSeconds());
	body.setFillColor(sf::Color(255, 255, 255, alphaChannel));

	if (speed != 0.f) {
		body.move(speed * std::cosf(angle), speed * std::sinf(angle));
	}
}
	