/******************************************************************************/
/*!
\file	Camera.h
\author Jun Xiang
\brief
To store camera position, target and up.
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class Camera:
\brief	To store camera position, target and up. With additional zoom function.
*/
/******************************************************************************/
class Camera
{
protected:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	float sensitivity;
public:
	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset(void);
	virtual void Update(double dt);

	virtual void setPosition(Vector3 position);
	virtual void setTarget(Vector3 target);
	virtual void setUp(Vector3 up);
	virtual void setSensitivity(float sensitivity);

	virtual Vector3 getPosition(void) const;
	virtual Vector3 getTarget(void) const;
	virtual Vector3 getUp(void) const;
	virtual float getSensitivity(void) const;
};

#endif