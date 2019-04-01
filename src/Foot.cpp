#include "Foot.h"

Foot::Foot(int rightSideL, Calf* calfL) :Limb(rightSideL, calfL)
{
	basePosition = glm::vec3(0.0f, -0.5f, 0.0f);

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.07f, 0.07f), glm::vec3(0.0f, 0.09f, 0.0f));
	createSegment(vertices, glm::vec2(0.05f, 0.05f), glm::vec3(0.0f, 0.03f, 0.0f));
	createSegment(vertices, glm::vec2(0.14f, 0.053f), glm::vec3(0.075f, -0.02f, 0.0f));
	createSegment(vertices, glm::vec2(0.15f, 0.054f), glm::vec3(0.08f, -0.06f, 0.0f));
	createSegment(vertices, glm::vec2(0.001f, 0.001f), glm::vec3(0.065f, -0.05f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;
}

Foot::~Foot()
{
}

int Foot::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	pitch = parent->pitch * 0.5f;

	pitch -= squat * 300.0f;

	draw(view, PartOfBody::texture, 1);

	return 0;
}