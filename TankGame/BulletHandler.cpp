#include "BulletHandler.h"
#include "Player.h"
#include <cmath>

BulletHandler::BulletHandler()
{
	bulletTexture.loadFromFile("Textures/bullet2.png");
}

BulletHandler::~BulletHandler()
{
}

void BulletHandler::update(sf::FloatRect boundingBox)
{
	for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {
		//update bullet
		(*bullet_itr).update();

		//if bullet is outside bounding box, delete bullet
		if (!boundingBox.contains((*bullet_itr).getPosition())) {
			bullet_itr = bulletList.erase(bullet_itr);
		}
		// elseif bullet colldes with enemy

		else { //bullet was within box, increment iterator
			++bullet_itr;
		}
	
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

void BulletHandler::hitDetection(Player * player)
{
	for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {

		float distance = std::hypotf(player->getPosition().x - (*bullet_itr).getPosition().x, player->getPosition().y - (*bullet_itr).getPosition().y );
		if (distance < (player->getSize() + (*bullet_itr).getSize())/2) {
			
			bullet_itr = bulletList.erase(bullet_itr);
			player->takeDamage();
		}
		// elseif bullet colldes with enemy

		else { //no bullet collision increment iterator
			++bullet_itr;
		}

	}
}

void BulletHandler::deleteBulletList()
{
	bulletList.clear();
}
