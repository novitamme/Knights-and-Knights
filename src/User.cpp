#include "User.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace User
{
	float User::manageMouseDirectives(float &yaw, int &attack)
	{
		float oldYaw = yaw;

		yaw += mouseOffset.x * mouseSensi;
		camYaw = yaw;

		camPitch += mouseOffset.y * mouseSensi;
		if (camPitch > 80.0f) camPitch = 80.0f;
		if (camPitch < -70.0f) camPitch = -70.0f;

		mouseOffset.x = 0;
		mouseOffset.y = 0;

		if(attack == 0) attack = attackCommand;
		attackCommand = 0;

		return (yaw - oldYaw);
	}

	glm::vec3 User::manageMoveDirectives(float deltaYaw, float walkSpeed, float runBoost, bool &isRunning)
	{
		glm::vec3 targetSpeed;

		if (moveCommand.x == 0) targetSpeed.x = 0.0f;
		else if (moveCommand.x == 1) targetSpeed.x = walkSpeed;
		else if (moveCommand.x == -1) targetSpeed.x = -walkSpeed * 0.7f;

		if (moveCommand.z == 0) targetSpeed.z = 0.0f;
		else if (moveCommand.z == 1) targetSpeed.z = walkSpeed * 0.8f;
		else if (moveCommand.z == -1) targetSpeed.z = -walkSpeed * 0.8f;

		float speedCoef = sqrt(abs(moveCommand.x) + abs(moveCommand.z));
		if (speedCoef != 0.0f) targetSpeed /= speedCoef;

		if (runCommand == 1)
		{
			targetSpeed *= runBoost;
			isRunning = 1;
		}
		else isRunning = 0;

		targetSpeed *= glm::max(((12.0f - abs(deltaYaw)) / 12.0f), 0.0f);

		return targetSpeed;
	}

	float User::manageJumpDirectives(float &deltaHeight, int &jump, float jumpSpeed)
	{
		float jumpVelocity = 0.0f;

		if (moveCommand.y == 1) jump--;

		deltaHeight = (float)jump / 50.0f;

		if ((moveCommand.y == 0 && jump < 0) || jump == -5)
		{
			jumpVelocity = -(float)jump * jumpSpeed / 5.0f;
			jump = 1;
			deltaHeight = 0.0f;
		}

		return jumpVelocity;
	}

	void User::updateCamera(glm::vec3 characterPosition)
	{
		camFront.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
		camFront.y = sin(glm::radians(camPitch));
		camFront.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
		camFront = glm::normalize(camFront);

		camRight = glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f)));
		camUp = glm::normalize(glm::cross(camRight, camFront));

		camPosition = glm::vec3(characterPosition.x - camFront.x * 4.5f, characterPosition.y + 3.5f, characterPosition.z - camFront.z * 4.5f);
	}

	glm::mat4 User::getViewMatrix()
	{
		return glm::lookAt(camPosition, camPosition + camFront, camUp);
	}

	glm::mat4 User::getStaticViewMatrix()
	{
		glm::vec3 pos = glm::vec3(0.0f, camPosition.y, 0.0f);

		return glm::lookAt(pos, pos + camFront, camUp);
	}

	glm::vec3 User::getCameraPosition()
	{
		return camPosition;
	}

	glm::vec2 mouseOffset = glm::vec2(0.0f, 0.0f);
	glm::ivec3 moveCommand = glm::ivec3(0, 0, 0);
	bool runCommand = false;
	int attackCommand = 0;
}