#include "Projectiles/Projectile.h"

Projectile::Projectile(sf::Vector2f pos, float rotation, int tankId, sf::Texture & texture, VisualEffectsHandler& vfxHandler)
	: vfxHandler(vfxHandler)
{
	body.setTexture(texture);
	body.setOrigin(sf::Vector2f(body.getTexture()->getSize().x * 0.5f, body.getTexture()->getSize().y  * 0.5f));
	body.setPosition(pos);
	body.setRotation(rotation);
	this->tankId = tankId;
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	float angle = body.getRotation() * gutils::degreesToRads;
	body.move(speed * std::cosf(angle), speed * std::sinf(angle));
	spawnTrail();
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::Vector2f Projectile::getPosition()
{
	return body.getPosition();
}

float Projectile::getSize()
{
	return size;
}

sf::Sprite Projectile::getSprite() {
	return body;
}

bool Projectile::shouldDelete()
{
	return expired;
}

void Projectile::hit()
{
	expired = true;
}

void Projectile::wallHit()
{
	if (wallBounces > 0) {
		--wallBounces;
		//TODO: change direction based on angle of incidence
		//temporary bounce implementation, rotate bullet 180 degrees
		body.rotate(180);
		float angle = body.getRotation() * gutils::degreesToRads;
		body.move(speed * std::cosf(angle), speed * std::sinf(angle));
		
	}
	else {
		expired = true;
	}
}

int Projectile::getTankId()
{
	return tankId;
}

void Projectile::spawnTrail()
{
	//To be implemented by child classes
}
