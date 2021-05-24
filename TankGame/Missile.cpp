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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		moveToTarget(getMousPos(window));
	}
	else
	{
		float angle = body.getRotation() / 180.f * M_PI;
		body.move(speed * std::cosf(angle), speed * std::sinf(angle));
	}
	
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

sf::Vector2f Missile::getMousPos(sf::RenderWindow & window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Missile::moveToTarget(sf::Vector2f targetPos)
{
	
	float angle = std::atan2f(targetPos.y - body.getPosition().y, targetPos.x - body.getPosition().x) * 180 / M_PI;
	angle = fmod(angle+360.f, 360.f);

	float delta = getDelta(angle,body.getRotation());

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
	
	float angle_r = body.getRotation() / 180 * M_PI;
	body.move(speed * std::cosf(angle_r), speed * std::sinf(angle_r));
}

float  Missile::getDelta(float a1, float a2) {
	
	float delta = a1 - a2;
	if (abs(delta) >= 180.f) {
		if (delta > 0) {

			delta -= 360.f;
		}
		else if (delta < 0) {
			delta += 360.f;
		}
	}
	return delta;
}
