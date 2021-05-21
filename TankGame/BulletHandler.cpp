#include "BulletHandler.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>

BulletHandler::BulletHandler()
{
	bulletTexture.loadFromFile("Textures/bullet.png");
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
	float p_size = player->getSize();
	sf::Vector2f p_pos = player->getPosition();

	for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {

		float distance = std::hypotf(p_pos.x - bullet_itr->getPosition().x, p_pos.y - bullet_itr->getPosition().y );
		if (distance < (p_size + bullet_itr->getSize())/2) {
			
			bullet_itr = bulletList.erase(bullet_itr);
			player->takeDamage();
		}
		// elseif bullet colldes with enemy

		else { //no bullet collision increment iterator
			++bullet_itr;
		}

	}
}

void BulletHandler::hitDetection(std::list<Enemy>* enemyList)
{
	float e_size = 0;
	sf::Vector2f e_pos(0.f, 0.f);
	bool kill = false;

	for (auto enemy_itr = enemyList->begin(); enemy_itr != enemyList->end(); ) {
		
		e_size = enemy_itr->getSize();
		e_pos = enemy_itr->getPosition();
		
		for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {

			float distance = std::hypotf(e_pos.x - bullet_itr->getPosition().x, e_pos.y - bullet_itr->getPosition().y);
			if (distance < (e_size + bullet_itr->getSize()) / 2) {

				bullet_itr = bulletList.erase(bullet_itr);
				if (enemy_itr->takeDamage()) {
					//enemy dead
					kill = true;
					break;
				}
			}
			// elseif bullet colldes with enemy

			else { //no bullet collision increment iterator
				++bullet_itr;
			}

		}

		if (kill) {
			enemy_itr = enemyList->erase(enemy_itr);
			kill = false;
		}
		else {
			++enemy_itr;
		}
	}
}

void BulletHandler::deleteBulletList()
{
	bulletList.clear();
}
