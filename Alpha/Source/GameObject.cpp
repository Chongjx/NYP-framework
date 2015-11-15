#include "GameObject.h"

GameObject::GameObject() : 
mesh(NULL),
name(""),
position(0, 0, 0),
render(false),
reflectLight(false),
update(false)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void GameObject::setName(string name)
{
	this->name = name;
}

void GameObject::setPosition(Vector3 position)
{
	this->position = position;

	this->TRS.translation.SetToTranslation(position);
}

void GameObject::setTRS(Properties _TRS)
{
	this->TRS = _TRS;
}

void GameObject::setRender(bool render)
{
	this->render = render;
}

void GameObject::setReflectLight(bool lighting)
{
	this->reflectLight = lighting;
}

void GameObject::setUpdate(bool update)
{
	this->update = update;
}

Mesh* GameObject::getMesh(void) const
{
	return this->mesh;
}

string GameObject::getName(void) const
{
	return this->name;
}

Vector3 GameObject::getPosition(void) const
{
	return this->position;
}

Properties GameObject::getProperties(void)
{
	Mtx44 overall;
	overall.SetToIdentity();

	TRS.modelProperties = overall * TRS.translation * TRS.rotation * TRS.scale;

	return TRS;
}

bool GameObject::getRender(void) const
{
	return this->render;
}

bool GameObject::getReflectLight(void) const
{
	return this->reflectLight;
}

bool GameObject::getUpdate(void) const
{
	return this->update;
}