#include "Collider.h"
#include "iostream"

Collider::Collider(glm::vec3 *globalPositionL, glm::vec3 positionL, float radiusL)
{
	position = positionL;
	globalPosition = globalPositionL;
	radius = radiusL;
}

Collider::~Collider()
{
}

bool Collider::checkCollision(glm::vec3 pointPosition)
{
	glm::vec3 positionDifference = (position + *globalPosition) - pointPosition;

	float distanceToMe = sqrt(pow(positionDifference.x, 2) + pow(positionDifference.y, 2) + pow(positionDifference.z, 2));

	if (distanceToMe < radius) return true;
	else return false;
}