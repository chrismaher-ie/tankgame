#include "Player.h"
static const float M_PI = 3.14159265358979f;

Player::Player() {
	body = sf::RectangleShape(sf::Vector2f(size, size));
	body.setOrigin(sf::Vector2f(size / 2, size / 2));
	body.setPosition(sf::Vector2f(0.f, 0.f));

	bodyTexture.loadFromFile("Textures/tankBase.png");
	body.setTexture(&bodyTexture);


	turret = sf::RectangleShape(sf::Vector2f(size, size));
	turret.setOrigin(sf::Vector2f(size / 2, size / 2));
	turret.setPosition(sf::Vector2f(0.f, 0.f));

	turretTexture.loadFromFile("Textures/tankTurret.png");
	turret.setTexture(&turretTexture);
}

Player::~Player()
{
}

void Player::update(sf::RenderWindow& window)
{
	//move player based on keypress
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		body.rotate(-0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		body.rotate(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		moveForward();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		moveBackward();
	}
	//twist turret to mouse
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(pixelPos);
	turret.setRotation(getAngle(turret.getPosition(), mouseWorldPos));

	//set turret to position 
	turret.setPosition(body.getPosition());
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(turret);
}

sf::Vector2f Player::getPosition()
{
	return body.getPosition();
}

void Player::moveForward()
{
	float angle = body.getRotation() / 180.f * M_PI;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Player::moveBackward()
{
	float angle = body.getRotation() / 180.f * M_PI;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

float Player::getAngle(sf::Vector2f v1, sf::Vector2f v2)
{
	float angle = std::atan2f(v2.y - v1.y, v2.x - v1.x) * 180 / M_PI;
	return angle;
}
