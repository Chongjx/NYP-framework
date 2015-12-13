#include "GameObject.h"

GameObject::GameObject() : 
mesh(NULL),
name(""),
position(0, 0, 0),
render(false),
reflectLight(true),
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

void GameObject::addPosition(Vector3 addPosition)
{
	this->position += addPosition;

	this->TRS.translation.SetToTranslation(position);
}

void GameObject::setRotation(float Angle, float x, float y, float z)
{
	this->rotation = Angle;

	this->TRS.rotation.SetToRotation(Angle,x,y,z);
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


void GameObject::setCollidable(bool collide)
{
	this->collidable = collide;
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

Vector3 GameObject::getMtxRotation(void) const
{
	return this->rotation;
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

bool GameObject::getCollidable(void) const
{
	return this->collidable;
}