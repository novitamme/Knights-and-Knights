#ifndef MATHS_H
#define MATHS_H

namespace Maths
{
	float fade(float x);
	float interpolate(float heightA, float heightB, float coef);
	float setPositionY(float corner[2][2], float dX, float dZ);
};
#endif