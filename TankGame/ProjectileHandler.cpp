#include "ProjectileHandler.h"
#include "Player.h"
#include "UnitTank.h"
#include <cmath>

ProjectileHandler::ProjectileHandler()
{
	bulletTexture.loadFromFile("Textures/bullet.png");
	missileTexture.loadFromFile("Textures/missile.png");
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::update(sf::FloatRect boundingBox)
{
	for (auto& projectile : projectileList) {
		projectile->update();

		if (!boundingBox.contains(projectile->getPosition())) {
			//TODO: calculate angle of wall that has been bit
			//pass wall angle in as parameter
			projectile->wallHit();
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
		std::unique_ptr<Projectile> projectile = std::make_unique<Bullet>(pos, rotation, tankId, bulletTexture);

		projectileList.push_back(std::move(projectile));
		break;
	}
	case MISSILETYPE:
	{
		std::unique_ptr<Projectile> projectile = std::make_unique<Missile>(pos, rotation, tankId, missileTexture);

		projectileList.push_back(std::move(projectile));
		break;
	}
	default:
		break;
	}
}

void ProjectileHandler::hitDetection(Player * player, std::list<UnitTank*>* tankList)
{
	float proj1Size;
	sf::Vector2f proj1Pos;

	float proj2Size;
	sf::Vector2f proj2Pos;

	float tankSize;
	sf::Vector2f tankPos;

	for (auto proj_itr1 = projectileList.begin(); proj_itr1 != projectileList.end(); ++proj_itr1) {
		proj1Size = (*proj_itr1)->getSize();
		proj1Pos = (*proj_itr1)->getPosition();
		
		//check projectile to projectile collisions
		//nested loop over single listprojectileList, no repeated checks or self comparision checks checks
		for (auto proj_itr2 = std::next(proj_itr1, 1); proj_itr2 != projectileList.end(); ++proj_itr2) {
			proj2Size = (*proj_itr2)->getSize();
			proj2Pos = (*proj_itr2)->getPosition();

			if (colliding(proj1Pos, proj2Pos, proj1Size, proj2Size)) {
				(*proj_itr1)->hit();
				(*proj_itr2)->hit();
			}

		}

		//check projectile to player collisions
		tankSize = player->getSize();
		tankPos = player->getPosition();
		if (colliding(proj1Pos, tankPos, proj1Size, tankSize)) {
			(*proj_itr1)->hit();
			player->takeDamage();
		}


		//check projectile to enemy collisions
		for (auto tank : (*tankList)) {
			tankSize = tank->getSize();
			tankPos = tank->getPosition();
			if (colliding(proj1Pos, tankPos, proj1Size, tankSize)) {
				(*proj_itr1)->hit();
				tank->takeDamage();
			}
		}
	}

	projectileList.remove_if([&](const std::unique_ptr<Projectile>& projectile) -> bool { return projectile->shouldDelete(); });
	tankList->remove_if([&](UnitTank* tank) -> bool { return tank->shouldDelete(); });
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

bool ProjectileHandler::colliding(sf::Vector2f pos1, sf::Vector2f pos2, float size1, float size2)
{
	//TODO: implement SAT collisions
	float distance = std::hypotf(pos1.x - pos2.x, pos1.y - pos2.y);
	if (distance < (size1 + size2) / 2) {
		return true;
	}
	else
	{
		return false;
	}
}
