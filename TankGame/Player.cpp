#include "Player.h"

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
		body.rotate(-speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		body.rotate(speed);
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
	turret.setRotation(gutils::getAngle(turret.getPosition(), mouseWorldPos));
	
	//set turret to position 
	turret.setPosition(body.getPosition());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (canShoot()) shoot();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		if (bulletHandler.missileList.empty()) fireMissile();
	}
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

BulletHandler* Player::getBulletHandler()
{
	return &bulletHandler;
}

float Player::getRotation()
{
	return body.getRotation();
}

void Player::takeDamage()
{
	if (--health == 0) {
		die();
	}
}

void Player::die()
{
	body.setPosition(200.f,200.f);
	health = 5;

}

float Player::getSize()
{
	return size;
}

float Player::getSpeed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		return 0.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		return speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		return speed * -1;
	}
	else {
		return 0.f;
	}
}

bool Player::canShoot()
{
	fireTimeDelta += fireRateClock.restart();
	if (fireTimeDelta > fireInterval) {
		fireTimeDelta = sf::seconds(0.f);
		return true;
	}
	return false;
}

void Player::shoot()
{
	float radian_angle = turret.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(turret.getPosition().x + (size/2 * std::cosf(radian_angle)), turret.getPosition().y + (size/2 *std::sinf(radian_angle)));
	bulletHandler.addBullet(bulletPos, turret.getRotation());
}

void Player::fireMissile()
{
	float radian_angle = turret.getRotation() * gutils::degreesToRads;
	sf::Vector2f bulletPos(turret.getPosition().x + (size / 2 * std::cosf(radian_angle)), turret.getPosition().y + (size / 2 * std::sinf(radian_angle)));
	bulletHandler.addMissile(bulletPos, turret.getRotation());
}

void Player::moveForward()
{
	float angle = body.getRotation() * gutils::degreesToRads;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
}

void Player::moveBackward()
{
	float angle = body.getRotation() * gutils::degreesToRads;
	body.move(-speed * std::cosf(angle), -speed * std::sinf(angle));
}