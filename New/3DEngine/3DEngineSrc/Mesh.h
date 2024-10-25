#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "AABB.h"

using std::string;
using std::vector;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void unload();

	class VertexArray* getVertexArray() { return vertexArray; }
	const string& getShaderName() const { return shaderName; }
	float getRadius() const { return radius; }
	const AABB& getBox() const { return box; }

	void addTexture(Texture* texture);
	Texture* getTexture(size_t index);

	void setVertexArray(VertexArray* vertexArrayP);
	void setShaderName(const string& shaderNameP);
	void setRadius(float radiusP);
	void setBox(const AABB& boxP) { box = boxP; }

private:
	vector<Texture*> textures;
	class VertexArray* vertexArray;
	string shaderName;
	float radius; // Bounding sphere radius
	AABB box;
};

