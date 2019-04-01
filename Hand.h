#ifndef HAND_H
#define HAND_H

#include "Forearm.h"

class Hand :public Limb
{
	friend class Forearm;
	friend class Character;
	friend class Weapon;

	int attack;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Hand(int rightSideL, Forearm* torsoL);
	~Hand();
};
#endif