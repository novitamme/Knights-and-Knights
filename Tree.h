#ifndef TREE_H
#define TREE_H

#include "Mesh.h"

struct Node
{
	Node* parent;
	Node* child[2];

	glm::vec3 core;
	glm::vec3 verts[8];

	int level;
	bool visited;
};

class Tree :public Mesh
{
	friend class GroundLayer;

	int segments;
	glm::vec3 internalPos;
	glm::mat4 setModel();
	
public:

	static unsigned int texture;

	Tree(float thickness = 0.03, float divergency = 0.06, float segCoef = 0.028);
	~Tree();
};
#endif
