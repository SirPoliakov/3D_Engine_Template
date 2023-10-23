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
	bool getVisible() { return isVisible; }
	void setVisible(bool _IsVisible);


protected:
	Mesh* mesh;
	size_t textureIndex;
	bool isVisible;
};

