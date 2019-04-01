#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Mesh.h"

class Ellipsoid :public Mesh
{
protected:
	int segments;
	float yaw, pitch, roll;
	glm::vec3 basePosition;
	glm::mat4 transformationMatrix;

	glm::mat4 setModel();
	void createSegment(std::vector <float> &vertices, glm::vec2 radius, glm::vec3 translation);
	void createIndices(std::vector <int> &indices);
	void setTransformationMatrix(glm::mat4 baseModel);

public:
	Ellipsoid();
	~Ellipsoid();
};
#endif