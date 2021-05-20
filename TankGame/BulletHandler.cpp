#include "BulletHandler.h"

BulletHandler::BulletHandler()
{
	bulletTexture.loadFromFile("Textures/bullet2.png");
}

BulletHandler::~BulletHandler()
{
}

void BulletHandler::update()
{
	for (auto& bullet : bulletList) {
		bullet.update();
	}
}

void BulletHandler::draw(sf::RenderWindow & window)
{
	for (auto& bullet : bulletList) {
		bullet.draw(window);
	}
}

void BulletHandler::addBullet(sf::Vector2f pos, float rotation)
{
	Bullet bullet = Bullet(pos, rotation, bulletTexture);
	bulletList.push_back(bullet);
}

void BulletHandler::deleteBulletList()
{
	bulletList.clear();
}
