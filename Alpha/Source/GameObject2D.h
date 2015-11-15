#ifndef GAMEOBJECT_2D_H
#define GAMEOBJECT_2D_H

#include "GameObject.h"
#include "OBB2D.h"

class GameObject2D : virtual public GameObject
{
public:
	GameObject2D();
	~GameObject2D();

	void setHitbox(OBB2D hitbox);
	OBB2D getHitbox(void);

	void updateHitbox(void);

protected:
	OBB2D obbHitbox;
};

#endif