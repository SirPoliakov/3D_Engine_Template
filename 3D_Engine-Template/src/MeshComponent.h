#pragma once
#include "Component.h"
class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner);
	virtual ~MeshComponent();

	void draw(class Shader& shader);
	virtual void setMesh(class Mesh& meshP);
	void setTextureIndex(size_t textureIndexP);


protected:
	Mesh* mesh;
	size_t textureIndex;
};

