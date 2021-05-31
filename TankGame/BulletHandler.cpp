#include "BulletHandler.h"
#include "Player.h"
#include "UnitTank.h"
#include <cmath>

BulletHandler::BulletHandler()
{
	bulletTexture.loadFromFile("Textures/bullet.png");
	missileTexture.loadFromFile("Textures/missile.png");
}

BulletHandler::~BulletHandler()
{
}

void BulletHandler::update(sf::RenderWindow & window, sf::FloatRect boundingBox)
{
	for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {
		//update bullet
		(*bullet_itr)->update();

		//if bullet is outside bounding box, delete bullet
		if (!boundingBox.contains((*bullet_itr)->getPosition())) {
			bullet_itr = bulletList.erase(bullet_itr);
		}
		// elseif bullet colldes with enemy

		else { //bullet was within box, increment iterator
			++bullet_itr;
		}
	
	}

	for (auto missile_itr = missileList.begin(); missile_itr != missileList.end(); ) {
		//update missile
		(*missile_itr)->update(window);
		if ((*missile_itr)->expired) {
			missile_itr = missileList.erase(missile_itr);
		}

		else { //missile was within box, increment iterator
			++missile_itr;
		}

	}
}

void BulletHandler::draw(sf::RenderWindow & window)
{
	for (auto& bullet : bulletList) {
		bullet->draw(window);
	}

	for (auto& missile : missileList) {
		missile->draw(window);
	}
}

void BulletHandler::addBullet(sf::Vector2f pos, float rotation)
{
	Bullet *bullet = new Bullet(pos, rotation, bulletTexture);
	bulletList.push_back(bullet);
}

void BulletHandler::addMissile(sf::Vector2f pos, float rotation)
{
	Missile *missile = new Missile(pos, rotation, missileTexture);
	missileList.push_back(missile);
}

void BulletHandler::hitDetection(Player * player)
{
	float p_size = player->getSize();
	sf::Vector2f p_pos = player->getPosition();

	for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {

		float distance = std::hypotf(p_pos.x - (*bullet_itr)->getPosition().x, p_pos.y - (*bullet_itr)->getPosition().y );
		if (distance < (p_size + (*bullet_itr)->getSize())/2) {
			
			bullet_itr = bulletList.erase(bullet_itr);
			player->takeDamage();
		}
		// elseif bullet colldes with enemy

		else { //no bullet collision increment iterator
			++bullet_itr;
		}

	}
}

void BulletHandler::hitDetection(std::list<UnitTank*>* tankList)
{
	float e_size = 0;
	sf::Vector2f e_pos(0.f, 0.f);
	bool kill = false;

	for (auto tank_itr = tankList->begin(); tank_itr != tankList->end(); ) {
		
		e_size = (*tank_itr)->getSize();
		e_pos = (*tank_itr)->getPosition();
		
		for (auto bullet_itr = bulletList.begin(); bullet_itr != bulletList.end(); ) {

			float distance = std::hypotf(e_pos.x - (*bullet_itr)->getPosition().x, e_pos.y - (*bullet_itr)->getPosition().y);
			if (distance < (e_size + (*bullet_itr)->getSize()) / 2) {

				bullet_itr = bulletList.erase(bullet_itr);

				(*tank_itr)->takeDamage();
				if (true /* tank->dead*/) {//enemy dead
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
			tank_itr = tankList->erase(tank_itr);
			kill = false;
		}
		else {
			++tank_itr;
		}
	}
}

void BulletHandler::deleteBulletList()
{
	bulletList.clear();
}
