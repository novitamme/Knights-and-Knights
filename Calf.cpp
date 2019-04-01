#include "Calf.h"
#include <math.h>
#include "Thigh.h"
#include "Foot.h"

Calf::Calf(int rightSideL, Thigh *thighL) :Limb(rightSideL, thighL)
{
	basePosition = glm::vec3(0.0f, -0.45f, 0.0f);

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.085f, 0.08f), glm::vec3(0.0f, 0.0f, 0.0f));
	createSegment(vertices, glm::vec2(0.095f, 0.09f), glm::vec3(-0.005f, -0.1f, 0.0));
	createSegment(vertices, glm::vec2(0.085f, 0.08f), glm::vec3(-0.005f, -0.2f, -0.005f * rightSide));
	createSegment(vertices, glm::vec2(0.075f, 0.065f), glm::vec3(0.0f, -0.3f, 0.0f));
	createSegment(vertices, glm::vec2(0.065f, 0.055f), glm::vec3(0.0f, -0.4f, 0.0f));
	createSegment(vertices, glm::vec2(0.045f, 0.045f), glm::vec3(0.0f, -0.5f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;

	child = new Foot(rightSide, this);
}

Calf::~Calf()
{
}

int Calf::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	pitch = (6.0f - abs(parent->pitch) * (1.0f + 1.5f * signbit(parent->pitch)));

	pitch += squat * 600.0f;

	draw(view, PartOfBody::texture, 1);
	
	child->update(view, NULL, NULL, squat, NULL);

	return 0;
}