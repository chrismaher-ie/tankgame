#include "GeometryUtils.h"

float gutils::getAngle(sf::Vector2f v1, sf::Vector2f v2)
{
	// returns an angle between -π and π, which is scaled to -180 to 180
	float angle = std::atan2f(v2.y - v1.y, v2.x - v1.x) * radsToDegrees;
	
	//transform from -180 to 180 to 0 to 360
	if (angle < 0) {
		angle += 360;
	}
	return angle;

}
float gutils::getAngleDelta(float angle1, float angle2)
{
	float delta = angle1 - angle2;
	if (abs(delta) >= 180.f) {
		if (delta > 0) {

			delta -= 360.f;
		}
		else if (delta < 0) {
			delta += 360.f;
		}
	}
	return delta;
}
float gutils::getTargetLeadAngle(sf::Vector2f originPos,  sf::Vector2f targetPos, float targetRot, float targetSpeed, float projectileSpeed)
{
	float worldAngle = getAngle(originPos, targetPos);
	
	float bulletSpeedRatio = projectileSpeed / targetSpeed; //make a ratio of bullet speed/ player speed

	float relativeAngleRadians = (targetRot - worldAngle) * degreesToRads;
	float angleDelta = std::asin(sinf(relativeAngleRadians) / bulletSpeedRatio) * radsToDegrees;
	
	return worldAngle + angleDelta;
	//TODO extend to account for origin velocity

}