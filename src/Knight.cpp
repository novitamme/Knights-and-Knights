#include "Knight.h"

Knight::Knight(glm::vec3 positionL, bool AIL) :Character(positionL, AIL)
{
	torso = new Torso(&transformationMatrix);

	numberOfColliders = 3;
	collider = new Collider*[numberOfColliders];
	collider[0] = new Collider(&position, glm::vec3(0.0f, 1.2f, 0.0f), 0.25f);
	collider[1] = new Collider(&position, glm::vec3(0.0f, 1.55f, 0.0f), 0.25f);
	collider[2] = new Collider(&position, glm::vec3(0.0f, 1.9f, 0.0f), 0.12f);

	walkSpeed = 1.4f;
	runBoost = 2.2f;
	brakeSpeed = 0.4f;
	jumpSpeed = 4.0f;

	health = 100.0f;
	strength = 20.0f;

	takeWeapon(0, 1);
}

Knight::~Knight()
{
}

void Knight::navigate(std::vector<Character*> &enemies)
{
	glm::vec3 positionDifference = enemies[0]->position - position;
	float distanceToMe = sqrt(pow(positionDifference.x, 2) + pow(positionDifference.z, 2));


	glm::vec3 MeDirection = normalize(positionDifference);
	float angleToMe = atan(MeDirection.z / MeDirection.x);
	angleToMe = glm::degrees(angleToMe);
	if (MeDirection.x < 0.0f) angleToMe += 180.0f;

	if (seeingMe == 0)
	{
		yaw += float(rand() % 3) - 1.0f;
		targetSpeed.x = walkSpeed;

		if (abs(angleToMe - yaw) < 70.0f || distanceToMe < 30.0f) seeingMe = 1;
	}

	else
	{
		float targetYaw = angleToMe;
		float diff = targetYaw - yaw;
		if (diff > 180.0f) diff -= 360.0f;
		yaw += diff * 0.2;

		if (bothLegsOnGround == 1)
		{
			if (distanceToMe >= 5.0f) targetSpeed = glm::vec3(walkSpeed * runBoost, 0.0f, 0.0f);
			else if (distanceToMe < 5.0f && distanceToMe >= 3.5f) targetSpeed = glm::vec3(walkSpeed, 0.0f, 0.0f);
			else if (distanceToMe < 3.5f && distanceToMe >= 2.3f)
			{
				targetSpeed = glm::vec3(0.0f, 0.0f, walkSpeed * (float)(rand() % 3 - 1));
				if (rand() % 4 == 0) targetSpeed.x = walkSpeed * runBoost;
			}
			else if (distanceToMe < 1.7f) targetSpeed.x = -walkSpeed * runBoost;
		}

		if (attack == 0)
		{
			if (distanceToMe < 2.3f) attack = 1;
			else if (distanceToMe < 2.6f) attack = 2;
		}
	}
}