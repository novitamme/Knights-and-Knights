#ifndef MESH_H
#define MESH_H

#include "shader.h"
#include <vector>

class Mesh
{
protected:
	unsigned int VAO;
	int trianglesNumb;
	Shader* shader;

	virtual glm::mat4 setModel() = 0;
	void createMesh(std::vector<float>& verts, std::vector<int>& indices, int parameters);

public:
	Mesh();
	~Mesh();

	glm::vec3 position;
	void draw(glm::mat4 view, static unsigned int texture, bool reflect);

	static void createTexture(const char* path, unsigned int &texture);
	static glm::mat4 projection;
	static glm::vec3 lightPosition;
	static glm::vec3 light;
};
#endif
