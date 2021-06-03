#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"
#include "Missile.h"
//#include "Player.h"
//#include "UnitTank.h"
//Forward Declarations as BulletHandler needs Player and Player needs buller handler
class Player;
class UnitTank;

class BulletHandler : public sf::Drawable
{
	public:
		std::list<Bullet*> bulletList;
		std::list<Missile*> missileList;
		BulletHandler();
		~BulletHandler();
		void update(sf::RenderWindow & window, sf::FloatRect boundingBox);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void addBullet(sf::Vector2f pos, float rotation, int tankId);
		void addMissile(sf::Vector2f pos, float rotation, int tankId);
		void hitDetection(Player* player);
		void hitDetection(std::list<UnitTank*>* enemyList);
		void deleteBulletList();
		int countBulletsFromTank(int tankId);
		int countMissilesFromTank(int tankId);
	private:

		sf::Texture bulletTexture;
		sf::Texture missileTexture;
};

