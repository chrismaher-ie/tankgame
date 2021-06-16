#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Projectiles/Projectile.h"
#include "Projectiles/Bullet.h"
#include "Projectiles/Missile.h"
#include "Map/Map.h"
#include "VisualEffects/VisualEffectsHandler.h"
#include "Collision.h"
//#include "Tanks/TankHandler.h"

#define BULLETTYPE 1
#define MISSILETYPE 2

//Forward Declarations as ProjectileHandler needs TankHandler and TankHandler needs ProjectileHandler
class TankHandler;

class ProjectileHandler : public sf::Drawable
{
	public:
		std::list<std::unique_ptr<Projectile>> projectileList;

		ProjectileHandler(Map& map, VisualEffectsHandler& vfxHandler);
		~ProjectileHandler();
		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void addProjectile(sf::Vector2f pos, float rotation, int projectileType, int tankId);
		void hitDetection();
		void deleteProjectileList();
		int countTankProjectiles(int tankId);
		void setTankHandler(TankHandler& tankHandler);
	private:
		Map &map;
		VisualEffectsHandler& vfxHandler;
		TankHandler* tankHandler;
		sf::Texture bulletTexture;
		sf::Texture missileTexture;
};

