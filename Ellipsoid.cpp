#include "Ellipsoid.h"
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

Ellipsoid::Ellipsoid()
{
	segments = -1;
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
}

Ellipsoid::~Ellipsoid()
{
}

glm::mat4 Ellipsoid::setModel()
{	
	glm::mat4 model = transformationMatrix;
	return model;
}

void Ellipsoid::createSegment(std::vector <float> &vertices, glm::vec2 radius, glm::vec3 translation)
{
	for (int i = 0; i <= 7; i++)
	{
		vertices.push_back(translation.x + radius.x * sin((float)i / 8.0f * 6.284f));
		vertices.push_back(translation.y);
		vertices.push_back(translation.z + radius.y * cos((float)i / 8.0f * 6.284f));
		vertices.push_back(sin((float)i / 8.0f * 6.284f));
		vertices.push_back(0.0f);
		vertices.push_back(cos((float)i / 8.0f * 6.284f));
		vertices.push_back(i % 2);
		vertices.push_back(segments % 2);
	}
	segments++;
}

void Ellipsoid::createIndices(std::vector <int> &indices)
{
	for (int i = 0; i <= segments; i++) for (int j = 0; j <= 7; j++)
	{
		indices.push_back(8 * i + j);
		indices.push_back(8 * i + (j + 1) % 8);
		indices.push_back(8 * i + 8 + j);
		indices.push_back(8 * i + (j + 1) % 8);
		indices.push_back(8 * i + 8 + j);
		indices.push_back(8 * i + 8 + (j + 1) % 8);
	}
}

void Ellipsoid::setTransformationMatrix(glm::mat4 baseModel)
{
	baseModel = glm::translate(baseModel, basePosition);

	baseModel = glm::rotate(baseModel, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	baseModel = glm::rotate(baseModel, glm::radians(pitch), glm::vec3(0.0f, 0.0f, 1.0f));
	baseModel = glm::rotate(baseModel, glm::radians(roll), glm::vec3(1.0f, 0.0f, 0.0f));

	transformationMatrix = baseModel;
}