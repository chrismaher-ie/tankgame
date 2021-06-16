#include "Projectiles/ProjectileHandler.h"
#include "Tanks/PlayerTank.h"
#include "Tanks/UnitTank.h"
#include <cmath>

ProjectileHandler::ProjectileHandler(Map &map, VisualEffectsHandler& vfxHandler)
	: map(map), vfxHandler(vfxHandler)
{
	bulletTexture.loadFromFile("Assets/Textures/bullet.png");
	missileTexture.loadFromFile("Assets/Textures/missile.png");
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::update()
{
	std::list<Wall> *wallList = map.getWallList();
	sf::Sprite projectileSprite;
	sf::Sprite wallSprite;

	for (auto& projectile : projectileList) {
		projectile->update();
		projectileSprite = projectile->getSprite();

		for (auto wall : (*wallList)) {
			wallSprite = wall.getSprite();

			//TODO: calculate angle of wall that has been bit
			
			if (Collision::BoundingBoxTest(projectileSprite,wallSprite)) {
				//pass wall angle in as parameter
				projectile->wallHit();
			}
		}

		if (!map.getBoundingBox().contains(projectile->getPosition())) {
			//bullet is out of bounds, mark for deletion
			projectile->hit();
		}
	}

	projectileList.remove_if([&](const std::unique_ptr<Projectile> &projectile) -> bool { return projectile->shouldDelete(); });
}

void ProjectileHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& projectile : projectileList) {
		target.draw((*projectile));
	}

}

void ProjectileHandler::addProjectile(sf::Vector2f pos, float rotation, int projectileType, int tankId)
{
	
	switch (projectileType)
	{
	case BULLETTYPE:
	{
		std::unique_ptr<Projectile> projectile = std::make_unique<Bullet>(pos, rotation, tankId, bulletTexture, vfxHandler);

		projectileList.push_back(std::move(projectile));
		break;
	}
	case MISSILETYPE:
	{
		std::unique_ptr<Projectile> projectile = std::make_unique<Missile>(pos, rotation, tankId, missileTexture, vfxHandler);

		projectileList.push_back(std::move(projectile));
		break;
	}
	default:
		break;
	}
}

void ProjectileHandler::hitDetection(PlayerTank * playerTank, std::list<std::unique_ptr<UnitTank>>* tankList)
{
	sf::Sprite projectile1_sprite;
	sf::Sprite projectile2_sprite;
	sf::Sprite tankSprite;

	for (auto proj_itr1 = projectileList.begin(); proj_itr1 != projectileList.end(); ++proj_itr1) {
		projectile1_sprite = (*proj_itr1)->getSprite();
		
		//check projectile to projectile collisions
		//nested loop over single listprojectileList, no repeated checks or self comparision checks checks
		for (auto proj_itr2 = std::next(proj_itr1, 1); proj_itr2 != projectileList.end(); ++proj_itr2) {
			projectile2_sprite = (*proj_itr2)->getSprite();
			
			if (Collision::BoundingBoxTest(projectile1_sprite, projectile2_sprite)) {
				(*proj_itr1)->hit();
				(*proj_itr2)->hit();
			}

		}

		//check projectile to playerTank collisions
		tankSprite = playerTank->getSprite();
		
		if (Collision::BoundingBoxTest(projectile1_sprite, tankSprite)) {
			(*proj_itr1)->hit();
			playerTank->takeDamage();
		}

		//check projectile to tank collisions
		for (auto& tank : (*tankList)) {
			tankSprite = tank->getSprite();
			if (Collision::BoundingBoxTest(projectile1_sprite, tankSprite)) {
				(*proj_itr1)->hit();
				tank->takeDamage();
			}
		}
	}

	projectileList.remove_if([&](const std::unique_ptr<Projectile>& projectile) -> bool { return projectile->shouldDelete(); });
	tankList->remove_if([&](const std::unique_ptr<UnitTank>& tank) -> bool { return tank->shouldDelete(); });
}

void ProjectileHandler::deleteProjectileList()
{
	for (auto& projectile : projectileList)
	{
		projectile.reset();
	}
	projectileList.clear();
}

int ProjectileHandler::countTankProjectiles(int tankId)
{
	int count = 0;
	for (auto& projectile : projectileList) {
		if (projectile->getTankId() == tankId) ++count;
	}
	return count;
}