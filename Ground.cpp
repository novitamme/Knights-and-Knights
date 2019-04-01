#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ground.h"
#include "GroundLayer.h"
#include <thread>

Ground::Ground()
{
	GroundUnit::createTexture("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/grassbig.jpg", GroundUnit::texture);
	Tree::createTexture("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/bark.jpg", Tree::texture);

	groundLayer = new GroundLayer*[2];
	groundLayer[0] = new GroundLayer(5, 0, 14, 1);
	groundLayer[1] = new GroundLayer(14, 5, 6, 0);
}

Ground::~Ground()
{

}

void Ground::update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime)
{
	int newPosX = (cameraPosition.x + 50.0f) / 100.0f;
	if (cameraPosition.x < -50.0f) newPosX--;
	int newPosZ = (cameraPosition.z + 50.0f) / 100.0f;
	if (cameraPosition.z < -50.0f) newPosZ--;

	if (newPosX != GroundLayer::map.currentLocation.x || newPosZ != GroundLayer::map.currentLocation.y)
	{
		if (newPosX != GroundLayer::map.currentLocation.x) transform(newPosX, 0);
		else if (newPosZ != GroundLayer::map.currentLocation.y)	transform(newPosZ, 1);
	}
	
	for (int i = 0; i < 2; i++) groundLayer[i]->update(view);
}

void Ground::transform(int newPos, bool toConvert)
{
	if(toConvert == 1) GroundLayer::map.convert();

	int direction = newPos - GroundLayer::map.currentLocation.x;
	GroundLayer::map.currentLocation.x = newPos;

	float distanceToBorder = GroundLayer::map.location00.x + GroundLayer::map.currentLocation.x;

	if (direction == -1 && distanceToBorder < 16) GroundLayer::map.expandMap(0);
	else if (direction == 1 && GroundLayer::map.size.x - distanceToBorder < 16)	GroundLayer::map.expandMap(1);

	if (toConvert == 1) GroundLayer::map.convert();

	for (int j = 0; j < 2; j++) groundLayer[j]->moveArray(direction, toConvert);

//	std::thread t1([this, direction, toConvert]()
//	{
//		for (int j = 0; j < 2; j++) groundLayer[j]->createArray(direction, toConvert);
//	});
//	t1.detach();

	std::thread t1(&GroundLayer::createArray, groundLayer[0], direction, toConvert);
	t1.detach();
	std::thread t2(&GroundLayer::createArray, groundLayer[1], direction, toConvert);
	t2.detach();
}
