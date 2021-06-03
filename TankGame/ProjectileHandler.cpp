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
	for (auto bullet : bulletList) {
		bullet->update();

		if (!boundingBox.contains(bullet->getPosition())) {
			bullet->hit();
		}
	}

	bulletList.remove_if([&](Bullet* bullet) -> bool { return bullet->shouldDelete(); });

	for (auto missile : missileList) {
		missile->update();

		if (!boundingBox.contains(missile->getPosition())) {
			missile->hit();
		}
	}

	missileList.remove_if([&](Missile* missile) -> bool { return missile->shouldDelete(); });
}

void ProjectileHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto bullet : bulletList) {
		target.draw((*bullet));
	}

	for (auto missile : missileList) {
		target.draw((*missile));
	}
}

void ProjectileHandler::addBullet(sf::Vector2f pos, float rotation, int tankId)
{
	Bullet *bullet = new Bullet(pos, rotation, tankId, bulletTexture);
	bulletList.push_back(bullet);
}

void ProjectileHandler::addMissile(sf::Vector2f pos, float rotation, int tankId)
{
	Missile *missile = new Missile(pos, rotation, tankId, missileTexture);
	missileList.push_back(missile);
}

void ProjectileHandler::hitDetection(Player * player)
{
	float distance;
	float p_size = player->getSize();
	sf::Vector2f p_pos = player->getPosition();

	for (auto bullet : bulletList) {
		distance = std::hypotf(p_pos.x - bullet->getPosition().x, p_pos.y - bullet->getPosition().y);
		if (distance < (p_size + bullet->getSize()) / 2) {

			bullet->hit();
			player->takeDamage();
		}
	}

	bulletList.remove_if([&](Bullet* bullet) -> bool { return bullet->shouldDelete(); });
}

void ProjectileHandler::hitDetection(std::list<UnitTank*>* tankList)
{
	float e_size = 0;
	sf::Vector2f e_pos(0.f, 0.f);
	bool kill = false;

	for (auto tank : (*tankList)) {
		e_size = tank->getSize();
		e_pos = tank->getPosition();

		for (auto bullet : bulletList) {
			float distance = std::hypotf(e_pos.x - bullet->getPosition().x, e_pos.y - bullet->getPosition().y);
			if (distance < (e_size + bullet->getSize()) / 2) {
				bullet->hit();
				tank->takeDamage();
			}
		}
	}

	bulletList.remove_if([&](Bullet* bullet) -> bool { return bullet->shouldDelete(); });
	tankList->remove_if([&](UnitTank* tank) -> bool { return tank->shouldDelete(); });
}

void ProjectileHandler::deleteBulletList()
{
	bulletList.clear();
}

int ProjectileHandler::countBulletsFromTank(int tankId)
{
	int count = 0;
	for (auto bullet : bulletList) {
		if (bullet->getTankId() == tankId) ++count;
	}
	return count;
}

int ProjectileHandler::countMissilesFromTank(int tankId)
{
	int count = 0;
	for (auto missile : missileList) {
		if (missile->getTankId() == tankId) ++count;
	}
	return count;
}
