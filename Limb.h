#ifndef LIMB_H
#define LIMB_H

#include "PartOfBody.h"

class Limb :public PartOfBody
{
	friend class Character;

protected:
	PartOfBody *parent;
	Limb *child;
	int rightSide;

	void setPosition();
	
public:
	Limb(int rightSideL, PartOfBody* parentL);
	~Limb();
};
#endif