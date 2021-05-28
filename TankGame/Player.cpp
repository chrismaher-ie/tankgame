#include "Player.h"

Player::Player(sf::Vector2f pos, float rotation, int teamId, BulletHandler& bulletHandler, sf::RenderWindow& window)
	: UnitTank(pos, rotation, teamId, bulletHandler), window(window)
{
}

Player::~Player()
{
}

void Player::die()
{
	body.setPosition(200.f, 200.f);
	health = 5;
}

void Player::update()
{
	UnitTank::update();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		if (bulletHandler.missileList.empty()) fireMissile();
	}
}

void Player::move()
{
	//Turning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
	{	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		body.rotate(-maxSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		body.rotate(maxSpeed);
	}
	else 
	{	}

	// Forward and Back movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		currentSpeed = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		float angle = body.getRotation() * gutils::degreesToRads;
		body.move(maxSpeed * std::cosf(angle), maxSpeed * std::sinf(angle));
		currentSpeed = maxSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		float angle = body.getRotation() * gutils::degreesToRads;
		body.move(-maxSpeed * std::cosf(angle), -maxSpeed * std::sinf(angle));
		currentSpeed = -maxSpeed;
	}
	else {
		currentSpeed = 0;
	}
}

bool Player::aim()
{
	//twist turret to mouse
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	turret.setRotation(gutils::getAngle(turret.getPosition(), mouseWorldPos));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		return true;
	}
	return false;
}

void Player::fireMissile()
{
	float radian_angle = turret.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(turret.getPosition().x + (size / 2 * std::cosf(radian_angle)), turret.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler.addMissile(bulletPos, turret.getRotation());
}