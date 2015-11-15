#ifndef STATIC_GAMEOBJECT_H
#define STATIC_GAMEOBJECT_H

#include "GameObject.h"

class StaticGameObject : virtual public GameObject
{
public:
	StaticGameObject();
	~StaticGameObject();
};

#endif