#ifndef FOOT_H
#define FOOT_H

#include "Calf.h"

class Foot :public Limb
{
	friend class Calf;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Foot(int rightSideL, Calf* CalfL);
	~Foot();
};
#endif