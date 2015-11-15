#ifndef MOBILE_GAMEOBJECT_H
#define MOBILE_GAMEOBJECT_H

#include "GameObject.h"

class MobileGameObject : virtual public GameObject
{
public:
	MobileGameObject();
	~MobileGameObject();

	void setVelocity(Vector3 velocity);
	void setDirection(Vector3 direction);
	void setMass(float mass);

	Vector3 getVelocity(void) const;
	Vector3 getDirection(void) const;
	float getMass(void) const;
protected:
	Vector3 velocity;
	Vector3 direction;
	float mass;
};

#endif