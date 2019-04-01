#include "GroundUnit.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Maths.h"
#include <thread>

GroundUnit::GroundUnit(float cornerL[2][2], int fragmentation, bool isTree)
{
	if (fragmentation % 2 == 1) fragmentation--;

	trianglesNumb = fragmentation * fragmentation * 2;

	createVertices(cornerL, fragmentation);

	if (isTree == 1) tree = new Tree;
	else tree = nullptr;
}

GroundUnit::~GroundUnit()
{
}

void GroundUnit::createVertices(float cornerL[2][2], int fragmentation)
{
	for (int i = 0; i <= 1; i++) for (int j = 0; j <= 1; j++) corner[i][j] = cornerL[i][j];

	if(vertices.size() != 0) vertices.clear();

	int half = fragmentation / 2;
	float length = 100.0f / (float)fragmentation;
	for (int i = -half; i <= half; i++) for (int j = -half; j <= half; j++)
	{
		float dX = ((float)i + half) / fragmentation;
		float dZ = ((float)j + half) / fragmentation;

		vertices.push_back((float)i * length);
		vertices.push_back(Maths::setPositionY(corner, dX, dZ));
		vertices.push_back((float)j * length);

		float diff1 = corner[0][0] - corner[0][1];
		float diff2 = corner[1][0] - corner[1][1];
		float curveCoef = (-cos(dX * 6.28318f) + 1.0f) / 2.0f;
		float odchX = Maths::interpolate(diff1, diff2, dZ) * curveCoef;
		vertices.push_back(odchX);

		vertices.push_back(10);

		diff1 = corner[0][0] - corner[1][0];
		diff2 = corner[0][1] - corner[1][1];
		curveCoef = (-cos(dZ * 6.28318f) + 1.0f) / 2.0f;
		float odchZ = Maths::interpolate(diff1, diff2, dX) * curveCoef;
		vertices.push_back(odchZ);

		vertices.push_back((float)j);
		vertices.push_back((float)i);
	}

	loadingFinish = 0;

}

glm::mat4 GroundUnit::setModel()
{
	glm::mat4 model;
	model = glm::translate(model, position);
	return model;
}

unsigned int GroundUnit::texture;

