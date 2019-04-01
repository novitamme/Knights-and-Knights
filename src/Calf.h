#ifndef CALF_H
#define CALF_H

#include "Thigh.h"
#include "Foot.h"

class Calf :public Limb
{
	friend class Thigh;
	friend class Foot;

	int update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack);

public:
	Calf(int rightSideL, Thigh* thighL);
	~Calf();
};
#endif