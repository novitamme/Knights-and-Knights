#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>

class Collider
{
	friend class Character;
	glm::vec3 *globalPosition, position;
	float radius;

	bool checkCollision(glm::vec3 point);

public:
	Collider(glm::vec3 *globalPositionL, glm::vec3 positionL, float radiusL);
	~Collider();
};
#endif