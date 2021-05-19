#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"

class BulletHandler
{
	public:
		std::list<Bullet> bulletList;

		BulletHandler();
		~BulletHandler();
		void update();
		void draw(sf::RenderWindow& window);
		void addBullet(sf::Vector2f pos, float rotation);

	private:

		sf::Texture bulletTexture;
};

