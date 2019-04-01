#include "Weapon.h"

Weapon::Weapon(glm::mat4 *handMatrixL)
{
	yaw = 0.0f;
	roll = 0.0f;
	pitch = -90.0f;

	handMatrix = handMatrixL;
	basePosition = glm::vec3(0.0f, -0.05f, 0.0f);
}

Weapon::~Weapon()
{
}

void Weapon::update(glm::mat4 view)
{
	position = glm::vec3(*handMatrix * glm::vec4(basePosition, 1.0f));
	setTransformationMatrix(*handMatrix);

	draw(view, Weapon::texture, 1);
}

glm::vec3 Weapon::setCheckpointPosition(int number)
{
	glm::vec3 checkpointPosition = glm::vec3(transformationMatrix * glm::vec4(checkpoint[number], 1.0f));
	return checkpointPosition;
}

unsigned int Weapon::texture;