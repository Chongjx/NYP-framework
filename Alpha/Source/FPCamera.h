/******************************************************************************/
/*!
\file	FPCamera.h
\author Jun Xiang
\brief
FPS camera system
*/
/******************************************************************************/
#ifndef FP_CAMERA_H
#define FP_CAMERA_H

#include "Camera.h"

/******************************************************************************/
/*!
Class FPCamera:
\brief	First Person Camera System
*/
/******************************************************************************/
class FPCamera : public Camera
{
public:
	enum CAM_TYPE
	{
		LAND_CAM,
		AIR_CAM,
		NUM_CAMTYPE
	};
private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view;
	float defaultSensitivity;
	CAM_TYPE sCameraType;

	bool m_bJumping;
	bool m_bCrouching;
	bool m_bCollideGround;
	float GRAVITY;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;
	bool m_bRecoil;
public:
	FPCamera();
	~FPCamera();

	float rotationX;
	float rotationY;
	float recoil;
	bool myKeys[255];

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float floorLevel);
	virtual void UpdateJump(const double dt, float heightOffset);
	virtual void UpdateStatus(const unsigned char key);
	virtual void Reset(void);

	virtual void SetCameraType(CAM_TYPE sCameraType);
	virtual void setPosition(Vector3 position);
	virtual void setTarget(Vector3 target);
	virtual void setUp(Vector3 up);
	virtual void setSensitivity(float sensitivity);
	virtual void setJumping(bool jumping);
	virtual void setRecoiling(bool recoiling);

	virtual CAM_TYPE GetCameraType(void);
	virtual Vector3 getPosition(void) const;
	virtual Vector3 getTarget(void) const;
	virtual Vector3 getUp(void) const;
	virtual Vector3 getView(void) const;
	virtual float getSensitivity(void) const;
	virtual bool getRecoiling(void) const;
	virtual bool getCollideGround(void) const;

	// basic methods
	virtual void moveForward(const double dt, float heightOffset, bool run = false);
	virtual void moveBackward(const double dt, float heightOffset, bool run = false);
	virtual void moveLeft(const double dt, float heightOffset);
	virtual void moveRight(const double dt, float heightOffset);
	virtual void moveUp(const double dt, float heightOffset);
	virtual void moveDown(const double dt, float heightOffset);

	virtual void lookLeft(const double dt);
	virtual void lookRight(const double dt);
	virtual void lookUp(const double dt);
	virtual void lookDown(const double dt);
	virtual void lookUp(const double dt, float upValue);
	virtual void lookDown(const double dt, float downValue);
	virtual void SpinClockwise(const double dt);
	virtual void SpinCounterClockwise(const double dt);

	// applied methods
	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);
	virtual void Walk(const double dt, float heightOffset);
	virtual void Run(const double dt, float heightOffset);
	virtual void Strafe(const double dt, float heightOffset);
	virtual void Crouch(const double dt, float heightOffset);
	virtual void Jump(const double dt);
};

#endif