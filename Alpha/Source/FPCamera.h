#ifndef FP_CAMERA_H
#define FP_CAMERA_H

#include "Camera.h"

class FPCamera// : public Camera
{
public:
	FPCamera();
	~FPCamera();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
};

#endif