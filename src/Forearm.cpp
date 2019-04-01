#include "Forearm.h"
#include "Arm.h"
#include "Hand.h"

Forearm::Forearm(int rightSideL, Arm* armL) :Limb(rightSideL, armL)
{
	basePosition = glm::vec3(0.0f, -0.4f, 0.0f);
	
	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.063f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f));
	createSegment(vertices, glm::vec2(0.062f, 0.07f), glm::vec3(-0.003f, -0.1f, 0.005f * rightSide));
	createSegment(vertices, glm::vec2(0.06f, 0.065f), glm::vec3(-0.002f, -0.2f, 0.003f * rightSide));
	createSegment(vertices, glm::vec2(0.056f, 0.056f), glm::vec3(0.0f, -0.3f, 0.0f));
	createSegment(vertices, glm::vec2(0.051f, 0.045f), glm::vec3(0.0f, -0.37f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;

	child = new Hand(rightSide, this);
}

Forearm::~Forearm()
{
}

int Forearm::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();

	if (attack == 0) pitch = parent->pitch + 14.0f;

	else if (attack == 1)
	{
		if (rightSide == 1)
		{
			pitch = parent->pitch * 0.3f;
		}
	}

	else if (attack == 2)
	{
		if (rightSide == 1)
		{
			yaw = parent->roll;
		}
	}

	draw(view, Limb::texture, 1);

	child->update(view, NULL, NULL, NULL, attack);

	return 0;
}