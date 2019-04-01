#include "Head.h"
#include "Torso.h"

Head::Head(int rightSideL, Torso* torsoL) :Limb(rightSideL, torsoL)
{
	basePosition = glm::vec3(0.0f, 0.8f, 0.0f);

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.16f, 0.16f), glm::vec3(0.0f, -0.03f, 0.0f));
	createSegment(vertices, glm::vec2(0.13f, 0.13f), glm::vec3(0.0f, 0.25f, 0.0f));
	createSegment(vertices, glm::vec2(0.01f, 0.01f), glm::vec3(0.0f, 0.26f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;
}

Head::~Head()
{
}

int Head::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	draw(view, Limb::texture, 1);

	return 0;
}