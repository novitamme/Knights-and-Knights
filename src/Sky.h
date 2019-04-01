#ifndef SKY_H
#define SKY_H

#include "Mesh.h"

class Sky :public Mesh
{

public:
	Sky(float peak);
	~Sky();
	glm::mat4 setModel();

};
#endif