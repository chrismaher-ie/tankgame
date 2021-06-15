#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Projectiles/Projectile.h"
#include "Projectiles/Bullet.h"
#include "Projectiles/Missile.h"
#include "Map/Map.h"
#include "VisualEffects/VisualEffectsHandler.h"
#include "Collision.h"
//#include "Tanks/Player.h"
//#include "Tanks/UnitTank.h"

#define BULLETTYPE 1
#define MISSILETYPE 2

//Forward Declarations as ProjectileHandler needs Player and Player needs ProjectileHandler
class Player;
class UnitTank;

class ProjectileHandler : public sf::Drawable
{
	public:
		std::list<std::unique_ptr<Projectile>> projectileList;

		ProjectileHandler(Map& map, VisualEffectsHandler& vfxHandler);
		~ProjectileHandler();
		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void addProjectile(sf::Vector2f pos, float rotation, int projectileType, int tankId);
		void hitDetection(Player* player, std::list<std::unique_ptr<UnitTank>>* enemyList);
		void deleteProjectileList();
		int countTankProjectiles(int tankId);
	private:
		Map &map;
		VisualEffectsHandler& vfxHandler;

		sf::Texture bulletTexture;
		sf::Texture missileTexture;
};

