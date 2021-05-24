#pragma once
#include <SFML/Graphics.hpp>

namespace gutils
{
	const float PI = static_cast<float>(std::atan2(0, -1)); //3.14159265358979f;
	const float degreesToRads = PI / 180.f;
	const float radsToDegrees = 180.f / PI;

	// Angle between 2 points
	float getAngle(sf::Vector2f v1, sf::Vector2f v2);
	float getAngleDelta(float angle1, float angle2);

	float getTargetLeadAngle(sf::Vector2f originPos, sf::Vector2f targetPos, float targetRot, float targetSpeed, float projectileSpeed);

};

