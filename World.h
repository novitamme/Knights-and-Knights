#ifndef WORLD_H
#define WORLD_H

#include "Cosmos.h"
#include "Ground.h"
#include "Population.h"

class World
{
	float deltaTime;
	float lastFrame;

	Object** staticComponents;
	Object** dynamicComponents;

public:
	World(glm::mat4 projection);
	~World();

	void update();
};
#endif
