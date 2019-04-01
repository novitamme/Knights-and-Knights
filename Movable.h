#ifndef MOVABLE_H
#define MOVABLE_H

#include <glm/glm.hpp>

class Movable
{
	friend class Torso;
	friend class Limb;
	friend class Character;
	friend class Knight;

protected:
	float yaw, pitch, roll;
	glm::vec3 up, front, right;
	glm::mat4 transformationMatrix;
	float brakeSpeed;
	glm::vec3 position, acceleration, velocity, targetSpeed;
	int jump;
	float deltaHeight;
	
	void updateDirectionVectors();
	void updateKinematics(float deltaTime, bool runs);
	float setGroundPosition();
	void jumpManaging(float groundHeight, float deltaTime);
	void setTransformationMatrix();

public:
	Movable();
	~Movable();

	static float gravity;
};
#endif