#include "Sword.h"
#include "Weapon.h"

Sword::Sword(glm::mat4 *handMatrixL) :Weapon(handMatrixL)
{
	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.03f, 0.025f), glm::vec3(0.0f, -0.1f, 0.0f));
	createSegment(vertices, glm::vec2(0.03f, 0.025f), glm::vec3(0.0f, 0.1f, 0.0f));
	createSegment(vertices, glm::vec2(0.25f, 0.025f), glm::vec3(0.0f, 0.13f, 0.0f));
	createSegment(vertices, glm::vec2(0.25f, 0.022f), glm::vec3(0.0f, 0.15f, 0.0f));
	createSegment(vertices, glm::vec2(0.13f, 0.008f), glm::vec3(0.0f, 0.18f, 0.0f));
	createSegment(vertices, glm::vec2(0.11f, 0.007f), glm::vec3(0.0f, 0.88f, 0.0f));
	createSegment(vertices, glm::vec2(0.001f, 0.001f), glm::vec3(0.0f, 0.93f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;

	numberOfCheckpoints = 3;
	checkpoint = new glm::vec3[3];
	checkpoint[0] = glm::vec3(0.0f, 0.31f, 0.0f);
	checkpoint[1] = glm::vec3(0.0f, 0.62f, 0.0f);
	checkpoint[2] = glm::vec3(0.0f, 0.93f, 0.0f);
}

Sword::~Sword()
{
}