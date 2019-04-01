#include "Tree.h"
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

Tree::Tree(float thickness, float divergency, float segCoef)
{
	Node first;
	first.core = glm::vec3(0, 0, 0);
	first.level = 0;
	first.parent = nullptr;
	Node *pointer = &first;

	int end = 0;
	segments = -1;

	std::vector <float> vertices;
	while (end == 0)
	{
		segments++;
																	// Set shape of new node
		for (int i = 0; i < 8; i++)
		{
			pointer->verts[i].x = pointer->core.x + (sin(i * 6.29f / 8) + (rand() % 20 / 40.0f))  * (16 - pointer->level) * thickness;
			pointer->verts[i].y = pointer->core.y;
			pointer->verts[i].z = pointer->core.z + (cos(i * 6.29f / 8) + (rand() % 20 / 40.0f))  * (16 - pointer->level) * thickness;
		}
																	// Fill vector of vertices
		if (pointer->level != 0)
		{
			for (int i = 0; i < 8; i++)
			{
				vertices.push_back(pointer->parent->verts[i].x);
				vertices.push_back(pointer->parent->verts[i].y);
				vertices.push_back(pointer->parent->verts[i].z);
				vertices.push_back(sin(i * 6.29 / 8));
				vertices.push_back(0);
				vertices.push_back(cos(i * 6.29 / 8));
				vertices.push_back(i % 2);
				vertices.push_back(0);
			}
			for (int i = 0; i < 8; i++)
			{
				vertices.push_back(pointer->verts[i].x);
				vertices.push_back(pointer->verts[i].y);
				vertices.push_back(pointer->verts[i].z);
				vertices.push_back(sin(i * 6.29 / 8));
				vertices.push_back(0);
				vertices.push_back(cos(i * 6.29 / 8));
				vertices.push_back(i % 2);
				vertices.push_back(1);
			}
		}
																	// Create child's node core
		if (rand() % 20 > 21 - pointer->level)
		{
			pointer->child[0] = new Node;
			pointer->child[0]->core = glm::vec3( pointer->core.x + (rand() % 40 - 20.0f) * divergency,   pointer->core.y + (rand() % 20 + 30.0f) * segCoef,   pointer->core.z + (rand() % 40 - 20.0f) * divergency );
			pointer->child[0]->parent = pointer;

			pointer->child[1] = new Node;
			pointer->child[1]->core = glm::vec3( pointer->core.x - (rand() % 40 - 20.0f) * divergency,   pointer->core.y + (rand() % 20 + 30.0f) * segCoef,   pointer->core.z - (rand() % 40 - 20.0f) * divergency );
			pointer->child[1]->parent = pointer;
		}
		else
		{
			pointer->child[0] = new Node;
			pointer->child[0]->core = glm::vec3( pointer->core.x + (rand() % 10 - 5.0f) * divergency,   pointer->core.y + (rand() % 20 + 30.0f) * segCoef,    pointer->core.z + (rand() % 10 - 5.0f) * divergency );
			pointer->child[0]->parent = pointer;
			
			pointer->child[1] = nullptr;
		}
																	// Next node
		if (pointer->level != 16) pointer = pointer->child[0];
		else
		{
			if (segments > 80) end = 1;

			do
			{
				pointer = pointer->parent;

				if (pointer->level == 0)
				{
					end = 1;
					break;
				}
			} while (pointer->child[1] == nullptr || pointer->child[1]->visited == 1);

			if (pointer->level != 0)
			{	
				pointer = pointer->child[1];
				pointer->visited = 1;
			}
		}
		if (pointer->level != 0) pointer->level = pointer->parent->level + 1;
	}

	std::vector <int> indices;
	for (int i = 0; i <= segments; i++) for (int j = 0; j <= 7; j++)
	{
		indices.push_back( 16 * i  +  j );
		indices.push_back( 16 * i  + (j + 1 ) % 8 );
		indices.push_back( 16 * i  +  j + 8 );

		indices.push_back( 16 * i     + (j + 1) % 8);
		indices.push_back( 16 * i + 8 +  j);
		indices.push_back( 16 * i + 8 + (j + 1) % 8);
	}

	trianglesNumb = segments * 16;

	createMesh(vertices, indices, 3);

	internalPos.x = rand() % 100 - 50.0f;
	internalPos.z = rand() % 100 - 50.0f;
}

Tree::~Tree()
{
}

glm::mat4 Tree::setModel()
{
	glm::mat4 model;
	model = glm::translate(model, (position + internalPos));
	return model;
}

unsigned int Tree::texture;