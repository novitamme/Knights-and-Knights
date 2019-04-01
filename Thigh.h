#ifndef THIGH_H
#define THIGH_H

#include "Torso.h"
#include "Calf.h"

class Thigh :public Limb
{
	friend class Torso;
	friend class Calf;

	bool isRolling;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Thigh(int rightSideL, PartOfBody* torsoL);
	~Thigh();
};
#endif