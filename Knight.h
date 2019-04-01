#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"

class Knight :public Character
{
	void navigate(std::vector<Character*> &enemies);

public:
	Knight(glm::vec3 positionL, bool AIL);
	~Knight();

};
#endif