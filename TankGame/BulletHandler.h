#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"
//#include "Player.h"
//Forward Declaration as BulletHandler needs Player and Player needs buller handler
class Player;

class BulletHandler
{
	public:
		std::list<Bullet> bulletList;

		BulletHandler();
		~BulletHandler();
		void update(sf::FloatRect boundingBox);
		void draw(sf::RenderWindow& window);
		void addBullet(sf::Vector2f pos, float rotation);
		void hitDetection(Player* player);
		void deleteBulletList();

	private:

		sf::Texture bulletTexture;
};

