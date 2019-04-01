#include "GroundLayer.h"
#include <glm/glm.hpp>
#include "GroundUnit.h"
#include "Ground.h"
#include "Maths.h"

GroundLayer::GroundLayer(int highBorderL, int lowBorderL, int fragmentationL, bool isForest)
{
	radius = highBorderL;
	size = radius * 2 + 1;
	lowBorder = lowBorderL;
	fragmentation = fragmentationL;

	for (int i = 0; i < fragmentation; i++) for (int j = 0; j < fragmentation; j++)
	{
		indices.push_back(i * (fragmentation + 1) + j);
		indices.push_back(i *(fragmentation + 1) + j + 1);
		indices.push_back((i + 1) * (fragmentation + 1) + j);
		indices.push_back(i * (fragmentation + 1) + j + 1);
		indices.push_back((i + 1) * (fragmentation + 1) + j);
		indices.push_back((i + 1) * (fragmentation + 1) + j + 1);
	}

	float corner[2][2];
	land = new GroundUnit**[size];
	for (int i = 0; i < size; i++)
	{
		land[i] = new GroundUnit*[size];

		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k <= 1; k++) for (int l = 0; l <= 1; l++) corner[k][l] = map.height[map.location00.x - radius + i + l][map.location00.y - radius + j + k];

			land[i][j] = new GroundUnit(corner, fragmentation, isForest);
			land[i][j]->position = glm::vec3((i - radius) * 100.0f, 0.0f, (j - radius) * 100.0f);
		}
	}

	visibilityMap = new bool*[size];
	for (int i = 0; i < size; i++)
	{
		visibilityMap[i] = new bool[size];

		for (int j = 0; j < size; j++)
		{
			int distanceX = abs(land[i][j]->position.x / 100 - map.currentLocation.x);
			int distanceZ = abs(land[i][j]->position.z / 100 - map.currentLocation.y);

			if (distanceX >= lowBorder || distanceZ >= lowBorder) visibilityMap[i][j] = 1;
			else visibilityMap[i][j] = 0;
		}
	}
}

GroundLayer::GroundLayer(const GroundLayer &groundLayer)
{
	size = groundLayer.size;
	lowBorder = groundLayer.lowBorder;
	radius = groundLayer.radius;
	fragmentation = groundLayer.fragmentation;

	land = new GroundUnit**[size];
	visibilityMap = new bool*[size];
	for (int i = 0; i < size; i++)
	{
		land[i] = new GroundUnit*[size];
		visibilityMap[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			land[i][j] = groundLayer.land[i][j];
			visibilityMap[i][j] = groundLayer.visibilityMap[i][j];
		}
	}
}

GroundLayer::~GroundLayer()
{
}

void GroundLayer::update(glm::mat4 view)
{
	for (int i = 0; i < size; i++) for (int j = 0; j < size; j++)
	{
		if (land[i][j]->loadingFinish == 0)
		{
			land[i][j]->createMesh(land[i][j]->vertices, indices, 3);
			land[i][j]->loadingFinish = 1;


			if (land[i][j]->tree != nullptr)
			{
				land[i][j]->tree->position = land[i][j]->position;
				float dX = (land[i][j]->tree->internalPos.x + 50.0f) / 100.0f;
				float dZ = (land[i][j]->tree->internalPos.z + 50.0f) / 100.0f;
				land[i][j]->tree->position.y = Maths::setPositionY(land[i][j]->corner, dX, dZ) - 1.0f;
			}

		}

		if (land[i][j]->loadingFinish == 1 && visibilityMap[i][j] == 1)
		{
			land[i][j]->draw(view, GroundUnit::texture, 0);
			if(land[i][j]->tree != nullptr) land[i][j]->tree->draw(view, Tree::texture, 0);
		}
	}
}

void GroundLayer::moveArray(int direction, bool axis)
{
	int begin = 1000;

	if (direction == 1) begin = 0;
	else if (direction == -1) begin = size - 1;

	if (begin == 1000) std::cout << "Not compatible data in Ground::moveArray function";
	
	else
	{
		GroundUnit** vic;
		vic = new GroundUnit*[size - 1];

		if (axis == 0) for (int j = 0; j < size; j++) vic[j] = land[begin][j];
		else for (int j = 0; j < size; j++)  vic[j] = land[j][begin];

		for (int i = 0; i < size - 1; i++)
		{
			if (axis == 0) for (int j = 0; j < size; j++)  land[begin][j] = land[begin + direction][j];
			else for (int j = 0; j < size; j++)  land[j][begin] = land[j][begin + direction];

			begin += direction;
		}

		if (axis == 0) for (int j = 0; j < size; j++)  land[begin][j] = vic[j];
		else for (int j = 0; j < size; j++)  land[j][begin] = vic[j];
	}
}

void GroundLayer::createArray(int direction, bool axis)
{
	glm::ivec2 row = glm::vec2( -radius, -radius );
	
	if (direction == 1)
	{
		if (axis == 0) row.x += radius * 2;
		if (axis == 1) row.y += radius * 2;
	}
	glm::ivec2 positionCoords = glm::vec2( row.x + map.currentLocation.x,  row.y + map.currentLocation.y );
	glm::ivec2 heightCoords = glm::vec2( positionCoords.x + map.location00.x,  positionCoords.y + map.location00.y );

	float corner[2][2];
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k <= 1; k++) for (int l = 0; l <= 1; l++)
		{
			corner[k][l] = map.height[ heightCoords.x + l + i * axis ][ heightCoords.y + k + i * !axis ];
		}
		if (axis == 0)
		{
			land[row.x + radius][i]->createVertices(corner, fragmentation);
			land[row.x + radius][i]->position = glm::vec3((positionCoords.x + i * axis) * 100.0f, 0.0f, (positionCoords.y + i * !axis) * 100.0f);
		}
		else
		{
			land[i][row.y + radius]->createVertices(corner, fragmentation);
			land[i][row.y + radius]->position = glm::vec3((positionCoords.x + i * axis) * 100.0f, 0.0f, (positionCoords.y + i * !axis) * 100.0f);
		}
	}
}

Map GroundLayer::map;