#include "Population.h"
#include "Knight.h"

Population::Population()
{
	Character** characters;
	characters = new Character*[3];

	characters[0] = new Knight(glm::vec3(0.0f, 0.0f, 0.0f), 0);
	goodGuys.push_back(characters[0]);

	characters[1] = new Knight(glm::vec3(20.0f, 0.0f, 50.0f), 1);
	enemies.push_back(characters[1]);
	characters[2] = new Knight(glm::vec3(20.0f, 0.0f, 60.0f), 1);
	enemies.push_back(characters[2]);
}

Population::~Population()
{
}

void Population::update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime)
{
	for (int i = 0; i < goodGuys.size(); i++) goodGuys[i]->update(view, cameraPosition, deltaTime, enemies);
	for (int i = 0; i < enemies.size(); i++) enemies[i]->update(view, cameraPosition, deltaTime, goodGuys);
}