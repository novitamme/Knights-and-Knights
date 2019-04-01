#include "Thigh.h"
#include "Torso.h"

Thigh::Thigh(int rightSideL, PartOfBody *torsoL) :Limb(rightSideL, torsoL)
{
	basePosition = glm::vec3(0.0f, 0.0f, 0.12f * rightSide);

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.09f, 0.09f), glm::vec3(0.0f, 0.0f, 0.0));
	createSegment(vertices, glm::vec2(0.13f, 0.12f), glm::vec3(0.0f, -0.05f, -0.01f * rightSide));
	createSegment(vertices, glm::vec2(0.12f, 0.115f), glm::vec3(0.01f, -0.15f, -0.005f * rightSide));
	createSegment(vertices, glm::vec2(0.12f, 0.105f), glm::vec3(0.0f, -0.25f, 0.0f));
	createSegment(vertices, glm::vec2(0.11f, 0.1f), glm::vec3(0.0f, -0.35f, 0.0f));
	createSegment(vertices, glm::vec2(0.095f, 0.09f), glm::vec3(0.0f, -0.4f, 0.0f));
	createSegment(vertices, glm::vec2(0.1f, 0.095f), glm::vec3(0.0f, -0.44f, 0.0f));
	createSegment(vertices, glm::vec2(0.095f, 0.09f), glm::vec3(0.0f, -0.48f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;

	child = new Calf(rightSide, this);
}

Thigh::~Thigh()
{
}

int Thigh::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	pitch = 3.0f + rhythm * (20.0f - 10.0f * isRolling ) * rightSide;
	roll = rhythm * 12.0f * rightSide * isRolling;

	pitch -= squat * 300.0f;

	draw(view, PartOfBody::texture, 1);

	child->update(view, NULL, NULL, squat, NULL);

	return 0;
}