#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Projectile.h"
#include "Bullet.h"
#include "Missile.h"
//#include "Player.h"
//#include "UnitTank.h"

#define BULLETTYPE 1
#define MISSILETYPE 2

//Forward Declarations as ProjectileHandler needs Player and Player needs buller handler
class Player;
class UnitTank;

class ProjectileHandler : public sf::Drawable
{
	public:
		std::list<std::unique_ptr<Projectile>> projectileList;

		ProjectileHandler();
		~ProjectileHandler();
		void update(sf::FloatRect boundingBox);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void addProjectile(sf::Vector2f pos, float rotation, int projectileType, int tankId);
		void hitDetection(Player* player, std::list<std::unique_ptr<UnitTank>>* enemyList);
		void deleteProjectileList();
		int countTankProjectiles(int tankId);
	private:

		sf::Texture bulletTexture;
		sf::Texture missileTexture;

		bool colliding(sf::Vector2f pos1, sf::Vector2f pos2, float size1, float size2);
};

