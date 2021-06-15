#include "Smoke.h"

Smoke::Smoke(sf::Vector2f pos, float rotation, float speed, sf::Texture& texture)
{
	body.setTexture(texture);
	body.setOrigin(sf::Vector2f(body.getTexture()->getSize().x * 0.5f, body.getTexture()->getSize().y  * 0.5f));
	body.setPosition(pos);
	body.setRotation(rotation);
	body.scale(sf::Vector2f(0.5f, 0.5f));

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

	//TODO bound alpha scaler between 0 and 1 regardless of expireTime length
	int alphaChannel = static_cast<int>(255 * (expireTime - elapsedTime).asSeconds());
	body.setColor(sf::Color(255, 255, 255, alphaChannel));

	if (speed != 0.f) {
		body.move(speed * std::cosf(angle), speed * std::sinf(angle));
	}
}
	