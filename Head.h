#ifndef HEAD_H
#define HEAD_H

#include "Limb.h"

class Head :public Limb
{
	friend class Torso;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Head(int rightSideL, Torso* torsoL);
	~Head();
};
#endif