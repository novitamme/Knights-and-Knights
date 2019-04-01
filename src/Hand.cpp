#include "Hand.h"

Hand::Hand(int rightSideL, Forearm* forearmL) :Limb(rightSideL, forearmL)
{
	basePosition = glm::vec3(0.0f, -0.37f, 0.0f);
	
	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.08f, 0.066f), glm::vec3(0.0f, 0.05f, 0.0f));
	createSegment(vertices, glm::vec2(0.06f, 0.05f), glm::vec3(0.0f, -0.0f, 0.0f));
	createSegment(vertices, glm::vec2(0.07f, 0.062f), glm::vec3(0.0f, -0.04f, 0.0f));
	createSegment(vertices, glm::vec2(0.065f, 0.06f), glm::vec3(0.0f, -0.08f, 0.0f));
	createSegment(vertices, glm::vec2(0.001f, 0.001f), glm::vec3(0.0f, -0.09f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;
}

Hand::~Hand()
{
}

int Hand::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	if (attack == 1)
	{
		if (rightSide == 1)
		{
			pitch = parent->pitch * -5.0f;
		}
	}

	else if (attack == 2)
	{
		if (rightSide == 1)
		{
			pitch = 10.f + parent->yaw * -2.5f;
		}
	}

	draw(view, Limb::texture, 1);

	return 0;
}