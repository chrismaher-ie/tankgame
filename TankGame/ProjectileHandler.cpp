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
	for (auto projectile : projectileList) {
		projectile->update();

		if (!boundingBox.contains(projectile->getPosition())) {
			projectile->hit();
		}
	}

	projectileList.remove_if([&](Projectile* projectile) -> bool { return projectile->shouldDelete(); });

}

void ProjectileHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto projectile : projectileList) {
		target.draw((*projectile));
	}

}

void ProjectileHandler::addProjectile(sf::Vector2f pos, float rotation, int projectileType, int tankId)
{
	Projectile *projectile;
	switch (projectileType)
	{
	case BULLETTYPE:
		projectile = new Bullet(pos, rotation, tankId, bulletTexture);
		projectileList.push_back(projectile);
		break;

	case MISSILETYPE:
		projectile = new Missile(pos, rotation, tankId, missileTexture);
		projectileList.push_back(projectile);
		break;
	default:
		break;
	}
}

void ProjectileHandler::hitDetection(Player * player)
{
	float distance;
	float tankSize = player->getSize();
	sf::Vector2f tankPos = player->getPosition();

	for (auto projectile : projectileList) {
		distance = std::hypotf(tankPos.x - projectile->getPosition().x, tankPos.y - projectile->getPosition().y);
		if (distance < (tankSize + projectile->getSize()) / 2) {
			projectile->hit();
			player->takeDamage();
		}
	}

	projectileList.remove_if([&](Projectile* projectile) -> bool { return projectile->shouldDelete(); });
}

void ProjectileHandler::hitDetection(std::list<UnitTank*>* tankList)
{
	float distance;
	float tankSize = 0;
	sf::Vector2f tankPos(0.f, 0.f);

	for (auto tank : (*tankList)) {
		tankSize = tank->getSize();
		tankPos = tank->getPosition();

		for (auto projectile : projectileList) {
			distance = std::hypotf(tankPos.x - projectile->getPosition().x, tankPos.y - projectile->getPosition().y);
			if (distance < (tankSize + projectile->getSize()) / 2) {
				projectile->hit();
				tank->takeDamage();
			}
		}
	}

	projectileList.remove_if([&](Projectile* projectile) -> bool { return projectile->shouldDelete(); });
	tankList->remove_if([&](UnitTank* tank) -> bool { return tank->shouldDelete(); });
}

void ProjectileHandler::deleteProjectileList()
{
	for (auto projectile : projectileList)
	{
		delete projectile;
	}
	projectileList.clear();
}

int ProjectileHandler::countTankProjectiles(int tankId)
{
	int count = 0;
	for (auto projectile : projectileList) {
		if (projectile->getTankId() == tankId) ++count;
	}
	return count;
}
