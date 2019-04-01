#include "PartOfBody.h"

PartOfBody::PartOfBody()
{
	shader = new Shader("C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/metalshader.vs.txt", "C:/Users/Przemek/Desktop/c/Grafika_1/Grafika_1/metalshader.fs.txt");
}

PartOfBody::~PartOfBody()
{
}

unsigned int PartOfBody::texture;