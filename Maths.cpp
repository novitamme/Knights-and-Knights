#include "Maths.h"

namespace Maths
{
	float fade(float x)
	{
		return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
	};

	float interpolate(float heightA, float heightB, float coef)
	{
		return heightA * (1.0f - coef) + heightB * coef;
	};

	float setPositionY(float corner[2][2], float dX, float dZ)
	{
		dX = fade(dX);
		dZ = fade(dZ);

		float component1 = interpolate(corner[0][0], corner[0][1], dX);
		float component2 = interpolate(corner[1][0], corner[1][1], dX);

		return interpolate(component1, component2, dZ);
	}
}