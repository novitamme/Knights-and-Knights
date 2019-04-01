#ifndef GROUNDLAYER_H
#define GROUNDLAYER_H

#include "GroundUnit.h"
#include "Map.h"

class GroundLayer
{
	friend class Ground;

	GroundUnit*** land;
	int size, lowBorder, radius, fragmentation;					
	
	bool** visibilityMap;
	std::vector <int> indices;

	void update(glm::mat4 view);
	void moveArray(int direction, bool axis);
	void createArray(int direction, bool axis);

public:
	GroundLayer(int highBorderL, int lowBorderL, int fragmentationL, bool isForest);
	GroundLayer(const GroundLayer &groundLayer);
	~GroundLayer();

	static Map map;
};
#endif