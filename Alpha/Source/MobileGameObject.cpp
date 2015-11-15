#include "MobileGameObject.h"

MobileGameObject::MobileGameObject() :
velocity(0, 0, 0),
direction(0, 0, 0),
mass(0)
{
}

MobileGameObject::~MobileGameObject()
{
}

void MobileGameObject::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}

void MobileGameObject::setDirection(Vector3 direction)
{
	this->direction = direction;
}

void MobileGameObject::setMass(float mass)
{
	this->mass = mass;
}

Vector3 MobileGameObject::getVelocity(void) const
{
	return velocity;
}

Vector3 MobileGameObject::getDirection(void) const
{
	return direction;
}

float MobileGameObject::getMass(void) const
{
	return mass;
}