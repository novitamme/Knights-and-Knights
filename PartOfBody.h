#ifndef PARTOFBODY_H
#define PARTOFBODY_H

#include "Ellipsoid.h"

class PartOfBody :public Ellipsoid
{
protected:
	friend class Limb;
	friend class Thigh;
	friend class Calf;
	friend class Foot;
	friend class Torso;
	friend class Arm;
	friend class Forearm;
	friend class Hand;
	friend class Weapon;

	virtual int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack) = 0;

public:
	PartOfBody();
	~PartOfBody();

	static unsigned int texture;
};
#endif