#ifndef USER_H
#define USER_H

#include <glm/glm.hpp>

namespace User
{
	extern glm::vec2 mouseOffset;
	static float mouseSensi = 0.2f, camYaw, camPitch;
	static glm::vec3 camPosition, camUp, camFront, camRight;
	extern glm::ivec3 moveCommand;
	extern bool runCommand;
	extern int attackCommand;

	float manageMouseDirectives(float &yaw, int &attack);
	glm::vec3 manageMoveDirectives(float deltaYaw, float walkSpeed, float runBoost, bool &isRunning);
	float manageJumpDirectives(float &deltaHeight, int &jump, float jumpSpeed);
	void updateCamera(glm::vec3 characterPosition);
	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix();   
	glm::mat4 getStaticViewMatrix(); 
};
#endif