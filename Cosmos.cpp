#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Cosmos.h"
#include "Sun.h"
#include "Sky.h"

Cosmos::Cosmos()
{
	mesh = new Mesh*[3];

	mesh[0] = new Sky(4000);
	mesh[1] = new Sky(-4000);
	mesh[2] = new Sun;
}

Cosmos::~Cosmos()
{
}

void Cosmos::update(glm::mat4 view, glm::vec3 CameraPosition, float deltaTime)
{
	for(int i = 0; i < 3; i++)
	{
		mesh[i]->draw(view, NULL, 0);
	}
}