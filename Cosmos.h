#ifndef COSMOS_H
#define COSMOS_H

#include "Object.h"

class Cosmos :public Object
{
	friend class World;

	Mesh** mesh;

	void update(glm::mat4 view, glm::vec3 CameraPosition, float deltaTime);

public:
	Cosmos();
	~Cosmos();
};
#endif