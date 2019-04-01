#ifndef SUN_H
#define SUN_H

#include "Mesh.h"

class Sun :public Mesh
{
	float sunAngle;

	void setPosition();
	glm::mat4 setModel();

public:

	Sun();
	~Sun();
};

#endif