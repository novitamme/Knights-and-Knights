#ifndef POPULATION_H
#define POPULATION_H

#include "Object.h"
#include "Character.h"

class Population :public Object
{
	friend class World;

	std::vector <Character*> goodGuys;
	std::vector <Character*> enemies;

	void update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime);

public:
	Population();
	~Population();
};
#endif