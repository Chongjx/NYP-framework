#ifndef TP_CAMERA_H
#define TP_CAMERA_H

#include "Camera.h"

class TPCamera// : public Camera
{
public:
	TPCamera();
	~TPCamera();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
};

#endif