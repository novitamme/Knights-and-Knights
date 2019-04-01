#include "Torso.h"
#include "Limb.h"
#include "Mesh.h"
#include "partOfBody.h"
#include <glm/glm.hpp>

Torso::Torso(glm::mat4* baseL)
{
	base = baseL;
	basePosition = glm::vec3(0.0f, 1.0f, 0.0f);

	std::vector <float> vertices;
	createSegment(vertices, glm::vec2(0.19f, 0.265f), glm::vec3(0.01f, -0.06f, 0.0f));
	createSegment(vertices, glm::vec2(0.17f, 0.265f), glm::vec3(0.0f, 0.0f, 0.0f));
	createSegment(vertices, glm::vec2(0.15f, 0.24f), glm::vec3(0.01f, 0.1f, 0.0f));
	createSegment(vertices, glm::vec2(0.14f, 0.2f), glm::vec3(0.02f, 0.2f, 0.0f));
	createSegment(vertices, glm::vec2(0.15f, 0.22f), glm::vec3(0.01f, 0.3f, 0.0f));
	createSegment(vertices, glm::vec2(0.16f, 0.26f), glm::vec3(-0.01f, 0.4f, 0.0f));
	createSegment(vertices, glm::vec2(0.19f, 0.27f), glm::vec3(0.0f, 0.5f, 0.0f));
	createSegment(vertices, glm::vec2(0.19f, 0.35f), glm::vec3(0.0f, 0.6f, 0.0f));
	createSegment(vertices, glm::vec2(0.13f, 0.12f), glm::vec3(0.01f, 0.7f, 0.0f));
	createSegment(vertices, glm::vec2(0.09f, 0.1f), glm::vec3(0.0f, 0.8f, 0.0f));

	std::vector <int> indices;
	createIndices(indices);

	createMesh(vertices, indices, 3);
	trianglesNumb = segments * 16;


	child = new Limb*[5];
	child[0] = new Thigh(1, this);
	child[1] = new Thigh(-1, this);
	child[2] = new Arm(1, this);
	child[3] = new Arm(-1, this);
	child[4] = new Head(0, this);
}

Torso::~Torso()
{
	for (int i = 0; i < 5; i++) delete child[i];
	delete child;
	delete base;
}

int Torso::update(glm::mat4 view, float rhythm, bool isRolling, float squat, int attack)
{
	position = glm::vec3(*base * glm::vec4(basePosition, 1.0f));
	setTransformationMatrix(*base);

	yaw = rhythm * float(1 + isRolling);
	
	draw(view, PartOfBody::texture, 1);

	bool endOfAttack = 0;
	for (int i = 0; i < 5; i++) if(child[i]->update(view, rhythm, isRolling, squat, attack) == 1) endOfAttack = 1;

	return (int)endOfAttack;
}

