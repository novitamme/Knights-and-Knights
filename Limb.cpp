#include "Limb.h"

Limb::Limb(int rightSideL, PartOfBody* parentL)
{
	parent = parentL;
	rightSide = rightSideL;
}

Limb::~Limb()
{
	if(child != nullptr) delete child;
}

void Limb::setPosition()
{
	position = glm::vec3(parent->transformationMatrix * glm::vec4(basePosition, 1.0f));
	setTransformationMatrix(parent->transformationMatrix);
}
