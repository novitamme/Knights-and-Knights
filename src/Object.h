#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"

class Object
{
public:
	Object();
	~Object();

	virtual void update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime) = 0;
};
#endif
