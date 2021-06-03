#pragma once
#include <SFML/Graphics.hpp>
#include "GeometryUtils.h"
#include "Projectile.h"

//Todo inherit from projectile class
class Bullet : public Projectile
{
public:
	Bullet(sf::Vector2f pos, float rotation, int tankId, sf::Texture& texture);
	~Bullet();

private:
	//NOTE: redeclarations of parent variables as below are ignored in parent methods
	// these variables have been set in the constructor
	//float speed = 0.6f;
	//float size = 8.0f;

};

