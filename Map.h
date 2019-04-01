#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>

class Map
{
	glm::ivec2 swapValues(glm::ivec2 data);

public:
	Map();
	Map(const Map& map);
	~Map();

	void expandMap(bool direction);
	void convert();

	float** height;
	glm::ivec2 size, location00, currentLocation;
};
#endif
