#ifndef ARM_H
#define ARM_H

#include "Torso.h"
#include "Limb.h"
#include "Forearm.h"

class Arm: public Limb
{
	friend class Torso;
	friend class Forearm;
	friend class Character;
	friend class Monster;
	friend class Me;

	bool endOfAttack;
	int attackFlag;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Arm(int rightSideL, Torso* torsoL);
	~Arm();

};
#endif