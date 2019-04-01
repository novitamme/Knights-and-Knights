#include "sun.h"
#include <GLFW/glfw3.h>
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"


Sun::Sun()
{
	shader = new Shader("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/sunshader.vs.txt", "C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/sunshader.fs.txt");

	std::vector <float> vertices;
	for (int i = 0; i <= 15; i++)
	{
		vertices.push_back(2000.0f);
		vertices.push_back(100.0f * sin((float)i / 16.0f * 6.284f));
		vertices.push_back(100.0f * cos((float)i / 16.0f * 6.284f));
	}
	vertices.push_back(2000.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	std::vector <int> indices;
	for (int i = 0; i <= 15; i++)
	{
		indices.push_back(i);
		indices.push_back((i + 1) % 16);
		indices.push_back(16);
	}

	createMesh(vertices, indices, 1);
	trianglesNumb = 16;
}

Sun::~Sun()
{
}

glm::mat4 Sun::setModel()
{
	setPosition();

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 840.0f, 0.0f));
	model = glm::rotate(model, sunAngle, glm::vec3(-1.0, 1.0, 0.0));
	model = glm::rotate(model, 0.785f, glm::vec3(0.0, 0.0, 1.0));
	return model;
}

void Sun::setPosition()
{
	sunAngle = -glfwGetTime() / 100;

	position.x = 2000 * cos(-sunAngle);
	position.z = 2000 * sin(-sunAngle);
	position.y = 2000 * cos(-sunAngle) + 1200;

	lightPosition = position;

	light = glm::vec3(1.0f, 1.0f, 1.0f) * ((position.y + 400) / 1080);

	if (position.y > 680.0f) light = glm::vec3(1.0f, 1.0f, 1.0f);

	if (position.y < 560.0f)
	{
		light.b = light.b * 2 - 0.89;
		if (light.b < 0.0f) light.b = 0;
	}

	if (position.y < 440.0f)
	{
		light.g = light.g * 2 - 0.78;
		if (light.g < 0.0f) light.g = 0;
	}

	if (position.y < -400.0f) light = glm::vec3(0.0f, 0.0f, 0.0f);
}