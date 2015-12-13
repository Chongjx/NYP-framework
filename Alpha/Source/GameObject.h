/******************************************************************************/
/*!
\file	GameObject.h
\author Chong Jun Xiang
\brief
Create a game object class which stores all its variables
*/
/******************************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "MatrixStack.h"
#include "MeshBuilder.h"
#include "Vector3.h"

using std::string;

static const Vector3 GRAVITY(0, -9.8f, 0);

/******************************************************************************/
/*!
Struct properties:
\brief	Consists of translation, rotation and scale of a basic object
*/
/******************************************************************************/
struct Properties
{
	Mtx44 modelProperties, translation, rotation, scale;

	Properties()
	{
		modelProperties.SetToIdentity();
		translation.SetToIdentity();
		rotation.SetToIdentity();
		scale.SetToIdentity();
	}
};

class GameObject
{
protected:
	Mesh* mesh;
	string name;
	Vector3 position;
	float rotation;
	Properties TRS;
	bool render;
	bool reflectLight;
	bool update;
	bool collidable;

public:
	GameObject();
	~GameObject(void);

	virtual void setMesh(Mesh* mesh);
	virtual void setName(string name);
	virtual void setPosition(Vector3 position);
	virtual void addPosition(Vector3 addPosition);
	virtual void setRotation(float Angle, float x, float y, float z);
	virtual void setTRS(Properties _TRS);
	virtual void setRender(bool render);
	virtual void setReflectLight(bool lighting);
	virtual void setUpdate(bool update);
	virtual void setCollidable(bool collide);

	virtual Mesh* getMesh(void) const;
	virtual string getName(void) const;
	virtual Vector3 getPosition(void) const;
	virtual Vector3 getMtxRotation(void) const;
	virtual Properties getProperties(void);
	virtual bool getRender(void) const;
	virtual bool getReflectLight(void) const;
	virtual bool getUpdate(void) const;
	virtual bool getCollidable(void) const;
};

#endif