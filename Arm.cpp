#include "Arm.h"
#include "Torso.h"

Arm::Arm(int rightSideL, Torso *torsoL) :Limb(rightSideL, torsoL)
{
	basePosition = glm::vec3(0.0f, 0.6f, 0.31f * rightSide);

	attackFlag = 0;

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.02f, 0.02f), glm::vec3(0.0f, 0.0f, 0.0f));
	createSegment(vertices, glm::vec2(0.08f, 0.063f), glm::vec3(0.002f, -0.03f, 0.0f));
	createSegment(vertices, glm::vec2(0.09f, 0.073f), glm::vec3(0.002f, -0.1f, 0.0f));
	createSegment(vertices, glm::vec2(0.08f, 0.063f), glm::vec3(0.0f, -0.16f, 0.0f));
	createSegment(vertices, glm::vec2(0.085f, 0.073f), glm::vec3(0.003f, -0.2f, 0.0f));
	createSegment(vertices, glm::vec2(0.085f, 0.068f), glm::vec3(0.002f, -0.3f, 0.005f * rightSide));
	createSegment(vertices, glm::vec2(0.07f, 0.06f), glm::vec3(0.0f, -0.41f, 0.003f * rightSide));
	createSegment(vertices, glm::vec2(0.075f, 0.07f), glm::vec3(0.0f, -0.44f, 0.002f * rightSide));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;

	child = new Forearm(rightSide, this);
}

Arm::~Arm()
{
}

int Arm::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	setPosition();
	
	if (attack == 0) pitch = rhythm * -14.0f * rightSide;

	else if (attack == 1)
	{
		endOfAttack = 0;
		if (rightSide == 1)
		{
			if (attackFlag == 0)
			{
				pitch += 11.0f;
				if (pitch > 60.0f) attackFlag = 1;
			}
			else if (attackFlag == 1)
			{
				pitch -= 15.0f;
				if (pitch < 0.0f)
				{
					attackFlag = 0;
					endOfAttack = 1;
				}
			}
			roll = pitch * 0.2f;
		}
	}

	else if (attack == 2)
	{
		endOfAttack = 0;
		if (rightSide == 1)
		{
			pitch -= 25.0f;
			roll = 15.0f * sin(pitch / 360.0f * 6.29f);

			if (pitch < -360.0f)
			{
				pitch = 0.0f;
				endOfAttack = 1;
			}
		}
	}

	pitch += squat * 100.0f;

	draw(view, PartOfBody::texture, 1);

	child->update(view, NULL, NULL, NULL, attack);

	if (attack != 0 && endOfAttack == 1) return 1;
	else return 0;
}