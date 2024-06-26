#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Mesh.h"

MeshComponent::MeshComponent(Actor* owner) : Component(owner), mesh(nullptr), textureIndex(0), isVisible(true)
{
	owner->getGame().getRenderer().addMesh(this);
}

MeshComponent::~MeshComponent()
{
	owner.getGame().getRenderer().removeMesh(this);
}

void MeshComponent::draw(Shader& shader)
{
	if (mesh)
	{
		Matrix4 wt = owner.getWorldTransform();
		shader.setMatrix4("uWorldTransform", wt);
		Texture* t = mesh->getTexture(textureIndex);
		if (t)
		{
			t->setActive();
		}
		VertexArray* va = mesh->getVertexArray();
		va->setActive();
		glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::setMesh(Mesh& meshP)
{
	mesh = &meshP;
}

void MeshComponent::setTextureIndex(size_t textureIndexP)
{
	textureIndex = textureIndexP;
}

void MeshComponent::setVisible(bool _IsVisible)
{
	isVisible = _IsVisible;
}
