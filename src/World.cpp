#include "World.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Maths.h"
#include "User.h"

World::World(glm::mat4 projection)
{
	PartOfBody::createTexture("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/fur.jpg", PartOfBody::texture);
	Weapon::createTexture("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/steel.jpg", Weapon::texture);

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	Mesh::projection = projection;
	Movable::gravity = -10.0f;

	staticComponents = new Object*[1];
	staticComponents[0] = new Cosmos;

	dynamicComponents = new Object*[2];
	dynamicComponents[0] = new Ground;
	dynamicComponents[1] = new Population;
}

World::~World()
{
}

void World::update()
{
	glm::vec3 cameraPosition = User::getCameraPosition();
	glm::mat4 static_view = User::getStaticViewMatrix();
	glm::mat4 dynamic_view = User::getViewMatrix();

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	for (int i = 0; i < 1; i++) staticComponents[i]->update(static_view, cameraPosition, deltaTime);
	for (int i = 0; i < 2; i++) dynamicComponents[i]->update(dynamic_view, cameraPosition, deltaTime);
}