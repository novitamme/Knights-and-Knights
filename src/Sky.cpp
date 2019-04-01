#include "Sky.h"
#include <vector>
#include "shader.h"
#include <glm/glm.hpp>

Sky::Sky(float peak)
{
	shader = new Shader("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/skyshader.vs.txt", "C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/skyshader.fs.txt");

	std::vector <float> vertices;
	for (int i = 0; i <= 15; i++)
	{
		vertices.push_back(sin((float)i / 16.0f * 6.284f) * 4000.0f);
		vertices.push_back(-60.0f);
		vertices.push_back(cos((float)i / 16.0f * 6.284f) * 4000.0f);
		vertices.push_back(sin((float)i / 16.0f * 6.284f));
		vertices.push_back(0.0f);
		vertices.push_back(cos((float)i / 16.0f * 6.284f));
	}
	vertices.push_back(0.0f);
	vertices.push_back(peak);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);


	std::vector <int> indices;
	for (int i = 0; i <= 15; i++)
	{
		indices.push_back(i);
		indices.push_back((i + 1) % 16);
		indices.push_back(16);
	}

	createMesh(vertices, indices, 2);
	trianglesNumb = 16;
}

Sky::~Sky()
{
}

glm::mat4 Sky::setModel()
{
	glm::mat4 model;
	return model;
}