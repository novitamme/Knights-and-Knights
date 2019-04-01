#include "Map.h"
#include <glm/glm.hpp>

Map::Map()
{
	size = glm::ivec2(35, 35);
	location00 = glm::ivec2(17, 17);
	currentLocation = glm::ivec2(0, 0);

	height = new float*[size.x];
	for (int i = 0; i < size.x; i++)
	{
		height[i] = new float[size.y];
		for (int j = 0; j < size.y; j++) height[i][j] = (float)(rand() % 40 - 15);
	}
}

Map::Map(const Map& map)
{
	size = map.size;
	location00 = map.location00;
	currentLocation = map.currentLocation;

	height = new float*[size.x];
	for (int i = 0; i < size.x; i++)
	{
		height[i] = new float[size.y];
		for (int j = 0; j < size.y; j++) height[i][j] = map.height[i][j];
	}
}

Map::~Map()
{
}

void Map::expandMap(bool direction)
{
	size.x++;
	location00.x += !direction;

	int emptyRow = (size.x - 1) * direction;

	float** current;
	current = new float*[size.x];
	for (int i = 0; i < size.x; i++)
	{
		current[i] = new float[size.y];

		if (i == emptyRow) for (int j = 0; j < size.y; j++)
		{
			if (j == 0) current[i][j] = height[i - direction][j] + rand() % 40 - 15;
			else current[i][j] = (height[i - direction][j] + current[i][j - 1]) / 2 + rand() % 40 - 15;
		}
		else for (int j = 0; j < size.y; j++) current[i][j] = height[i - !direction][j];
	}

	height = new float*[size.x];
	for (int i = 0; i < size.x; i++)
	{
		height[i] = new float[size.y];
		for (int j = 0; j < size.y; j++) height[i][j] = current[i][j];
	}

//	for (int i = 0; i < size.y; i++) delete[] current[i];
//	delete [] current;
}

void Map::convert()
{
	size = swapValues(size);
	currentLocation = swapValues(currentLocation);
	location00 = swapValues(location00);

	float** current;
	current = new float*[size.x];
	for (int i = 0; i < size.x; i++)
	{
		current[i] = new float[size.y];
		for (int j = 0; j < size.y; j++) current[i][j] = height[j][i];
	}

	height = current;

//	for (int i = 0; i < size.y; i++) delete[] current[i];
//	delete[] current;
}

glm::ivec2 Map::swapValues(glm::ivec2 data)
{
	glm::ivec2 newVec = glm::ivec2(data.y, data.x);
	return newVec;
}