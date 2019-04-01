#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movable.h"
#include "Torso.h"
#include "Collider.h"
#include "Weapon.h"

class Character: public Movable
{
	friend class Population;

protected:
	float rhythm, moveBegin;
	bool isLiving, isMoving, rightFootMoving, isRunning, runControl, bothLegsOnGround;
	float walkSpeed, runBoost, jumpSpeed;
	Torso* torso;
	Collider **collider;
	int numberOfColliders;
	Weapon *weapon;
	int attack;
	bool AI, seeingMe;
	float health, strength;
	int hit;

	void update(glm::mat4 view, glm::vec3 CameraPosition, float deltaTime, std::vector<Character*> &enemies);
	void updateMove(float deltaTime);
	void setRhythm();
	float setMoveFluct();
	void takeWeapon(int leftHand, int kindOfWeapon);
	void updateAvatar(glm::mat4 view);	
	bool checkWeaponCollision(std::vector<Character*> &enemies);
	void getDirectivesFromUser();
	virtual void navigate(std::vector<Character*> &enemies) = 0;

public:
	Character(glm::vec3 positionL, bool AIL);
	~Character();
};
#endif