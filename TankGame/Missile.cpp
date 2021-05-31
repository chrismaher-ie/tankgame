#include "Missile.h"

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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		moveToTarget(getMousPos(window));
	}
	else
	{
		float angle = body.getRotation() * gutils::degreesToRads;
		body.move(speed * std::cosf(angle), speed * std::sinf(angle));
	}
	
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::Vector2f Missile::getPosition()
{
	return body.getPosition();
}

float Missile::getSize()
{
	return size;
}

sf::Vector2f Missile::getMousPos(sf::RenderWindow & window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Missile::moveToTarget(sf::Vector2f targetPos)
{
	float angle = gutils::getAngle(body.getPosition(), targetPos);

	float delta = gutils::getAngleDelta(angle,body.getRotation());

	if (abs(delta) > turnSpeed) { 
	
		if (delta > 0) {
			body.rotate(1 * turnSpeed);
		}
		if (delta < 0) {
			body.rotate(-1 * turnSpeed);
		}
	}
	else if (abs(delta) <= turnSpeed){
		body.rotate(delta);
	}
	
	float angle_r = body.getRotation() * gutils::degreesToRads;
	body.move(speed * std::cosf(angle_r), speed * std::sinf(angle_r));
}