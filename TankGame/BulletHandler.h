#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"
#include "Missile.h"
//#include "Player.h"
//#include "Enemy.h"
//Forward Declarations as BulletHandler needs Player and Player needs buller handler
class Player;
class Enemy;

class BulletHandler
{
	public:
		std::list<Bullet> bulletList;
		std::list<Missile> missileList;
		BulletHandler();
		~BulletHandler();
		void update(sf::RenderWindow & window, sf::FloatRect boundingBox);
		void draw(sf::RenderWindow& window);
		void addBullet(sf::Vector2f pos, float rotation);
		void addMissile(sf::Vector2f pos, float rotation);
		void hitDetection(Player* player);
		void hitDetection(std::list<Enemy>* enemyList);
		void deleteBulletList();

	private:

		sf::Texture bulletTexture;
		sf::Texture missileTexture;
};

