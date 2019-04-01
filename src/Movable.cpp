#include "Movable.h"
#include "GroundLayer.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Maths.h"

Movable::Movable()
{
}

Movable::~Movable()
{
}

void Movable::updateDirectionVectors()
{
	if (yaw > 270.0f) yaw -= 360.0f;
	if (yaw < -90.0f) yaw += 360.0f;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

void Movable::setTransformationMatrix()
{
	glm::mat4 model;

	model = glm::translate(model, position);

	model = glm::rotate(model, glm::radians(-yaw), up);
	model = glm::rotate(model, glm::radians(pitch), right);
	model = glm::rotate(model, glm::radians(roll), front);

	transformationMatrix = model;
}

void Movable::updateKinematics(float deltaTime, bool runs)
{
	if (deltaTime > 1.0f) deltaTime = 0.0f;

	acceleration.x = (targetSpeed.x - velocity.x) * (7.0f - runs * 5.0f);
	velocity.x += acceleration.x * deltaTime;
	if (targetSpeed.x == 0.0f && abs(velocity.x) < brakeSpeed) velocity.x = 0.0f;

	acceleration.z = (targetSpeed.z - velocity.z) * (7.0f - runs * 5.0f);
	velocity.z += acceleration.z * deltaTime;
	if (targetSpeed.z == 0.0f && abs(velocity.z) < brakeSpeed) velocity.z = 0.0f;
}

float Movable::setGroundPosition()
{
	float k[2][2];

	int sectorX = (position.x + 50.0f) / 100.0f;
	if (position.x < -50.0f) sectorX--;
	float dX = position.x / 100.0f - sectorX + 0.5f;

	int sectorZ = (position.z + 50.0f) / 100.0f;
	if (position.z < -50.0f) sectorZ--;
	float dZ = position.z / 100.0f - sectorZ + 0.5f;

	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
	{
		k[i][j] = GroundLayer::map.height[GroundLayer::map.location00.x + sectorX + j][GroundLayer::map.location00.y + sectorZ + i];
	}

	float groundPosition = Maths::setPositionY(k, dX, dZ);
	return groundPosition;
}

void Movable::jumpManaging(float groundHeight, float deltaTime)
{
	if (jump == 1)
	{
		velocity.y += gravity * deltaTime;
		position.y += velocity.y * deltaTime;

		if (position.y < groundHeight && velocity.y < 0.0f) jump = 2;
	}
	else if (jump == 2)
	{
		velocity.y += 30.0f * deltaTime;
		deltaHeight += velocity.y * deltaTime;

		deltaHeight = glm::max(deltaHeight, -0.12f);

		if (deltaHeight > 0.0f)
		{
			jump = 0;
			deltaHeight = 0.0f;
		}
	}
}
