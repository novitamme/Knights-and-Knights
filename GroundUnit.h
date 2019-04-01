#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Tree.h"

class GroundUnit :public Mesh
{
	friend class GroundLayer;

	glm::mat4 setModel();
	
	float corner[2][2];
	std::vector <float> vertices;
	int loadingFinish;
	Tree* tree;
	
public:
	
	static unsigned int texture;

	void createVertices(float cornerL[2][2], int fragmentation);

	GroundUnit(float cornerL[2][2], int fragmentation, bool isTree);
	~GroundUnit();
};
#endif
