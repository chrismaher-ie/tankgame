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
		void update(sf::FloatRect boundingBox);
		void draw(sf::RenderWindow& window);
		void addBullet(sf::Vector2f pos, float rotation);
		void deleteBulletList();

	private:

		sf::Texture bulletTexture;
};

