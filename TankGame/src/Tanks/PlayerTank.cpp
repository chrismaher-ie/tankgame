#include "Tanks/PlayerTank.h"

PlayerTank::PlayerTank(sf::Vector2f pos, float rotation, int teamId, ProjectileHandler& projectileHandler, VisualEffectsHandler& vfxHandler, sf::RenderWindow& window)
	: UnitTank(pos, rotation, teamId, projectileHandler, vfxHandler), window(window)
{
	// override parent class members
	health = 5;
	maxSpeed = 0.3f;
	maxProjectiles = 3;

	fireRate = 5.f;

	body.setColor(sf::Color::Blue);
	turret.setColor(sf::Color::Blue);
}

PlayerTank::~PlayerTank()
{
}

void PlayerTank::die()
{
	body.setPosition(200.f, 200.f);
	health = 5;
}

void PlayerTank::update()
{
	UnitTank::update();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		if (canShoot()) {
			shoot(MISSILETYPE);
		}
	}
}

void PlayerTank::move()
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

bool PlayerTank::aim()
{
	//twist turret to mouse
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	turret.setRotation(gutils::getAngle(turret.getPosition(), mouseWorldPos));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		return true;
	}
	return false;
}