#ifndef GROUND_H
#define GROUND_H

#include "GroundLayer.h"
#include "Object.h"

class Ground :public Object
{
	friend class World;

	GroundLayer** groundLayer;

	void update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime);
	void transform(int newPos, bool toConvert);

public:
	Ground();
	~Ground();
};
#endif
