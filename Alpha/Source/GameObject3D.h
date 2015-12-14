#ifndef GAMEOBJECT_3D_H
#define GAMEOBJECT_3D_H

#include "GameObject.h"
#include "OBB3D.h"

class GameObject3D : virtual public GameObject
{
public:
	GameObject3D();
	~GameObject3D();

	void setHitbox(Vector3 midPoint, float length, float height, float depth, const string name);
	void setHitbox(OBB3D hitbox);
	OBB3D getHitbox(void);
	
	void updateHitbox(Vector3 finalPos);
	void updateHitbox(void);

protected:
	OBB3D obbHitbox;
};

#endif