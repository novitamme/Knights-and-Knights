#ifndef WEAPON_H
#define WEAPON_H

#include "PartOfBody.h"

class Weapon :public Ellipsoid
{
	friend class Character;

protected:
	glm::mat4 *handMatrix;
	int numberOfCheckpoints;
	glm::vec3 *checkpoint;

	glm::vec3 setCheckpointPosition(int number);
	void update(glm::mat4 view);

public:
	Weapon(glm::mat4 *handMatrixL);
	~Weapon();

	static unsigned int texture;
};
#endif