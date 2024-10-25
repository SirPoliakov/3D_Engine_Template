#include "Mesh.h"
#include "VertexArray.h"

Mesh::Mesh() : vertexArray(nullptr), shaderName(""), radius(0.0f), box(Vector3::infinity, Vector3::negInfinity)
{
}

Mesh::~Mesh()
{
}

void Mesh::unload()
{
	delete vertexArray;
	vertexArray = nullptr;
}

void Mesh::addTexture(Texture* texture)
{
	textures.emplace_back(texture);
}

Texture* Mesh::getTexture(size_t index)
{
	if (index < textures.size())
	{
		return textures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::setVertexArray(VertexArray* vertexArrayP)
{
	vertexArray = vertexArrayP;
}

void Mesh::setShaderName(const string& shaderNameP)
{
	shaderName = shaderNameP;
}

void Mesh::setRadius(float radiusP)
{
	radius = radiusP;
}

//void Mesh::setBox(const AABB& boxP)
//{
//	box = boxP;
//}
