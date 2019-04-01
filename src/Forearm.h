#ifndef FOREARM_H
#define FOREARM_H

#include "Arm.h"
#include "Hand.h"

class Forearm :public Limb
{
	friend class Arm;
	friend class Hand;
	friend class Character;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Forearm(int rightSideL, Arm* torsoL);
	~Forearm();
};
#endif