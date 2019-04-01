#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Character.h"
#include "Object.h"
#include <time.h>
#include "Weapon.h"
#include "Sword.h"
#include "User.h"

Character::Character(glm::vec3 positionL, bool AIL)
{
	isLiving = 1;
	position = positionL;
	jump = 0;
	isRunning = 0;
	isMoving = 0;
	bothLegsOnGround = 1;
	AI = AIL;
}

Character::~Character()
{
}

void Character::update(glm::mat4 view, glm::vec3 CameraPosition, float deltaTime, std::vector<Character*> &enemies)
{
	if (isLiving == 1)
	{
		setRhythm();

		if (AI == 1) navigate(enemies);
		else getDirectivesFromUser();

		if (hit == 0)
		{
			if (checkWeaponCollision(enemies) == 1)
			{
				targetSpeed.x = -4.0f;
				hit = 1;
			}
		}
		else
		{
			if (hit % 3 == 1) hit += 3;
			else if (hit % 3 == 0) hit -= 3;

			if (health <= 0)
			{
				if (hit > 42.0f) isLiving = 0;
			}
			else
			{
				if (hit > 9) hit = 9;
			}
			pitch = hit * 2.0f;
		}

		updateMove(deltaTime);
		if (jump != 1) position.y += setMoveFluct();
		setTransformationMatrix();
	}

	updateAvatar(view);
}

void Character::updateMove(float deltaTime)
{
	if (jump != 1)
	{
		updateDirectionVectors();
		updateKinematics(deltaTime, isRunning);
	}

	position += front * velocity.x * deltaTime;
	position += right * velocity.z * deltaTime;

	float groundHeight = setGroundPosition();
	if (jump != 1) position.y = groundHeight;     

	jumpManaging(groundHeight, deltaTime);
	position.y += deltaHeight;
}

void Character::setRhythm()
{
	if (velocity.x != 0.0f || velocity.z != 0.0f )
	{
		if (isMoving == 0) moveBegin = clock();
		isMoving = 1;
	}  
	else if (bothLegsOnGround == 1) isMoving = 0;

	if (runControl != isRunning)
	{
		moveBegin = clock() - (rightFootMoving * 314.2f * (2 - isRunning));
		runControl = isRunning;
	}

	rhythm = 1.1f * sin((clock() - moveBegin) / 100.0f / (2 - isRunning));
	if (rhythm > 1.0f) rhythm = 1.0f;
	else if (rhythm < -1.0f) rhythm = -1.0f;

	if (isMoving == 1)
	{
		bool isRightFootMoving = signbit(rhythm);
		if (isRightFootMoving != rightFootMoving) bothLegsOnGround = 1;
		else bothLegsOnGround = 0;
		rightFootMoving = isRightFootMoving;
	}
	else rhythm = 0.0f;
}

float Character::setMoveFluct()
{
	float resultantSpeed = sqrt(pow(velocity.x, 2) + pow(velocity.z, 2));
	rhythm *= (resultantSpeed / walkSpeed);


	float fluct = abs(rhythm);
	if (isRunning == 1) fluct *= 0.1f;
	else fluct *= -0.06f;

	return fluct;
}

void Character::takeWeapon(int leftHand, int kindOfWeapon)
{
	if (weapon != nullptr) delete weapon;

	glm::mat4 *handMatrix = &torso->child[2 + leftHand]->child->child->transformationMatrix;

	if (kindOfWeapon == 1) weapon = new Sword(handMatrix);
	//	else if (kindOfWeapon == 2) weapon = new Axe(handMatrix);
}

void Character::updateAvatar(glm::mat4 view)
{
	bool rolls;
	if (velocity.z != 0) rolls = 1;
	else rolls = 0;

	if (torso->update(view, rhythm, rolls, deltaHeight, attack) == 1) attack = 0;
	weapon->update(view);
}

bool Character::checkWeaponCollision(std::vector<Character*> &enemies)
{
	bool isHit = 0;

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->attack != 0)
		{
			for (int j = 0; j < enemies[i]->weapon->numberOfCheckpoints; j++)
			{
				glm::vec3 point = enemies[i]->weapon->setCheckpointPosition(j);

				for (int k = 0; k < numberOfColliders; k++)	if (collider[k]->checkCollision(point) == 1)
				{
					isHit = 1;

					float attackStrength = enemies[i]->strength * float(1 + enemies[i]->attack) / 2.0f;

					health -= attackStrength;
					break;
				}
			}
		}
		if (isHit == 1) break;
	}

	return isHit;
}

void Character::getDirectivesFromUser()
{
	float deltaYaw = User::manageMouseDirectives(yaw, attack);

	if(bothLegsOnGround == 1) targetSpeed = User::manageMoveDirectives(deltaYaw, walkSpeed, runBoost, isRunning);

	if (jump <= 0) velocity.y = User::manageJumpDirectives(deltaHeight, jump, jumpSpeed);

	User::updateCamera(position);
}

float Character::gravity;