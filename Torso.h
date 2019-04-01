#ifndef TORSO_H
#define TORSO_H

#include "Mesh.h"
#include "Ellipsoid.h"
#include "Limb.h"
#include "Thigh.h"
#include "Arm.h"
#include "Head.h"

class Torso :public PartOfBody
{
	friend class Character;
	friend class Monster;
	friend class Me;
	friend class Thigh;
	friend class Arm;
	friend class Head;

	glm::mat4 *base;
	Limb** child;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:

	Torso(glm::mat4 *baseL);
	~Torso();
};
#endif