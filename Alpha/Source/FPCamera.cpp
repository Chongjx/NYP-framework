/******************************************************************************/
/*!
\file	FPCamera.cpp
\author Jun Xiang
\brief
Camera funtions that calculate and return the latest position of the camera.
*/
/******************************************************************************/
#include "FPCamera.h"
#include "Application.h"
#include "Mtx44.h"

static const float WALK_SPEED = 100.f;
static const float TURN_SPEED = 200.f;
static const float RUN_SPEED = 400.f;
/******************************************************************************/
/*!
\brief
FPCamera default constructor
*/
/******************************************************************************/
FPCamera::FPCamera()
{
}

/******************************************************************************/
/*!
\brief
FPCamera default destructor
*/
/******************************************************************************/
FPCamera::~FPCamera()
{
}

/******************************************************************************/
/*!
\brief	Camera Init function

\param	pos
position vector3
\param	target
target vector3
\param	up
up vector3
*/
/******************************************************************************/
void FPCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->sensitivity = defaultSensitivity = 1.0f;

	sCameraType = LAND_CAM;

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}

	m_bCrouching = false;
	m_bCollideGround = true;
	m_bJumping = false;
	m_bRecoil = false;
	JumpVel = 0.0f;
	JUMPMAXSPEED = 200.f;
	JUMPACCEL = 100.f;
	GRAVITY = -100.f;

	rotationX = 0.f;
	rotationY = 0.f;
	recoil = 0.f;
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	dt
the time passed since last update
*/
/******************************************************************************/
void FPCamera::Update(double dt, float heightOffset)
{
	if (myKeys['w'])
	{
		if (myKeys['z'])
		{
			if (!m_bJumping)
			{
				Run(dt, heightOffset);
			}
			else
			{
				Walk(dt, heightOffset);
			}
			myKeys['z'] = false;
		}
		else
		{
			Walk(dt, heightOffset);
		}
		myKeys['w'] = false;
	}

	if (myKeys['s'])
	{
		if (myKeys['z'])
		{
			Run(-dt, heightOffset);
			myKeys['z'] = false;
		}
		else
		{
			Walk(-dt, heightOffset);
		}
		myKeys['s'] = false;
	}

	if (myKeys['a'])
	{
		Strafe(-dt, heightOffset);
		myKeys['a'] = false;
	}

	if (myKeys['d'])
	{
		Strafe(dt, heightOffset);
		myKeys['d'] = false;
	}

	if (myKeys['q'])
	{
		moveUp(dt, 5.f);
		myKeys['q'] = false;
	}

	if (myKeys['e'])
	{
		moveDown(dt, 5.f);
		myKeys['e'] = false;
	}

	if (myKeys[32])
	{
		Jump(dt);
		myKeys[32] = false;
	}

	if (myKeys['c'])
	{
		m_bCrouching = true;
		Crouch(dt, heightOffset);
		myKeys['c'] = false;
	}

	else
	{
		m_bCrouching = false;
		Crouch(-dt, heightOffset);
	}

	if (m_bRecoil)
	{
		static float timer = 0.f;

		lookUp(dt, 20.f);
		timer += (float)dt;

		if (timer >= 0.1f)
		{
			m_bRecoil = false;
			timer = 0.f;
		}
	}

	else if (!m_bRecoil && recoil > 0.f)
	{
		lookDown(dt, 20.f);
	}

	UpdateJump(dt, heightOffset);

	
	if (Application::getMouse()->getMousePitch() != 0)
	{
		Pitch(dt);
	}
	if (Application::getMouse()->getMouseYaw() != 0)
	{
		Yaw(dt);
	}

	if (myKeys['r'])
	{
		Reset();
		myKeys['r'] = false;
	}
}
/******************************************************************************/
/*!
\brief	Camera Update function

\param	dt
time passed since last update
\param heightOffset
terrain height
*/
/******************************************************************************/
void FPCamera::UpdateJump(const double dt, float heightOffset)
{
	if (m_bJumping)
	{
		m_bCollideGround = false;
		// Factor in gravity
		JumpVel += GRAVITY * (float)dt;

		// Update the camera and target position
		position.y += JumpVel * (float)dt;
		target.y += JumpVel * (float)dt;

		// check if the camera has reached the ground
		float yDiff = target.y - position.y;
		if (position.y <= heightOffset + 20.f)
		{
			position.y = heightOffset + 20.f;
			target.y = yDiff + position.y;
			JumpVel = 0.0f;
			m_bJumping = false;
			m_bCollideGround = true;
		}
	}
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	key
reflect the key that is pressed
*/
/******************************************************************************/
void FPCamera::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
}

/******************************************************************************/
/*!
\brief	reset position
*/
/******************************************************************************/
void FPCamera::Reset(void)
{
	this->position = defaultPosition;
	this->target = defaultTarget;
	this->up = defaultUp;
	this->sensitivity = defaultSensitivity;

	view = (target - position).Normalized();
	Vector3 right = view.Cross(up).Normalized();
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->sensitivity = defaultSensitivity = 1.0f;

	sCameraType = LAND_CAM;

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}

	m_bCrouching = false;
	m_bCollideGround = true;
	m_bJumping = false;
	m_bRecoil = false;
	JumpVel = 0.0f;
	JUMPMAXSPEED = 200.f;
	JUMPACCEL = 100.f;
	GRAVITY = -200.f;

	rotationX = 0.f;
	rotationY = 0.f;
	recoil = 0.f;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter function

\param	sCameraType
camera type
*/
/******************************************************************************/
void FPCamera::SetCameraType(CAM_TYPE sCameraType)
{
	this->sCameraType = sCameraType;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter function

\param	position
position vector3
*/
/******************************************************************************/
void FPCamera::setPosition(Vector3 position)
{
	this->position = position;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter functions

\param	target
target vector3
*/
/******************************************************************************/
void FPCamera::setTarget(Vector3 target)
{
	this->target = target;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter functions

\param	up
up vector3
*/
/******************************************************************************/
void FPCamera::setUp(Vector3 up)
{
	this->up = up;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter functions

\param	sensitivity
sensitivty of the mouse float
*/
/******************************************************************************/
void FPCamera::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter functions

\param	jumping
character jump
*/
/******************************************************************************/
void FPCamera::setJumping(bool jumping)
{
	this->m_bJumping = jumping;
}

/******************************************************************************/
/*!
\brief	FPCamera Setter functions

\param	recoiling
recoil of the mouse
*/
/******************************************************************************/
void FPCamera::setRecoiling(bool recoiling)
{
	this->m_bRecoil = recoiling;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	CAM_TYPE
camera type
*/
/******************************************************************************/
FPCamera::CAM_TYPE FPCamera::GetCameraType(void)
{
	return this->sCameraType;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	Vector3
position vector3
*/
/******************************************************************************/
Vector3 FPCamera::getPosition(void) const
{
	return position;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	Vector3
target vector3
*/
/******************************************************************************/
Vector3 FPCamera::getTarget(void) const
{
	return target;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	Vector3
up vector3
*/
/******************************************************************************/
Vector3 FPCamera::getUp(void) const
{
	return up;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	Vector3
view vector3
*/
/******************************************************************************/
Vector3 FPCamera::getView(void) const
{
	return view;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	float
mouse sensitivity float
*/
/******************************************************************************/
float FPCamera::getSensitivity(void) const
{
	return sensitivity;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	bool
mouse recoil
*/
/******************************************************************************/
bool FPCamera::getRecoiling(void) const
{
	return m_bRecoil;
}

/******************************************************************************/
/*!
\brief	FPCamera Getter functions

\return	bool
mouse recoil
*/
/******************************************************************************/
bool FPCamera::getCollideGround(void) const
{
	return m_bCollideGround;
}

// basic methods
void FPCamera::moveForward(const double dt, float heightOffset, bool run)
{
	float heightDiff = target.y - position.y;

	view = (target - position).Normalized();

	if (!run)
	{
		position += view * WALK_SPEED * (float)dt;
		target += view * WALK_SPEED * (float)dt;
	}

	else
	{
		position += view * RUN_SPEED * (float)dt;
		target += view * RUN_SPEED * (float)dt;
	}

	if (!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPCamera::moveBackward(const double dt, float heightOffset, bool run)
{
	float heightDiff = target.y - position.y;

	view = (target - position).Normalized();
	if (!run)
	{
		position -= view * WALK_SPEED * (float)dt;
		target -= view * WALK_SPEED * (float)dt;
	}
	else
	{
		position -= view * RUN_SPEED * (float)dt;
		target -= view * RUN_SPEED * (float)dt;
	}

	if (!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPCamera::moveLeft(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * WALK_SPEED * (float)dt;
	target -= right * WALK_SPEED * (float)dt;

	if (!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPCamera::moveRight(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * WALK_SPEED * (float)dt;
	target += right * WALK_SPEED * (float)dt;

	if (!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPCamera::moveUp(const double dt, float heightOffset)
{
	position.y += heightOffset * (float)dt;
	target.y += heightOffset * (float)dt;
}

void FPCamera::moveDown(const double dt, float heightOffset)
{
	position.y -= heightOffset * (float)dt;
	target.y -= heightOffset * (float)dt;
}

void FPCamera::lookLeft(const double dt)
{
	//Update the camera direction based on mouse move
	// left-right rotate
	view = (target - position).Normalized();
	float yaw = (float)(-TURN_SPEED * Application::getMouse()->getMouseYaw() * (float)dt);
	rotationY += yaw;
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPCamera::lookRight(const double dt)
{
	view = (target - position).Normalized();
	float yaw = (float)(-TURN_SPEED * Application::getMouse()->getMouseYaw() * (float)dt);
	rotationY += yaw;
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPCamera::lookUp(const double dt)
{
	float pitch = (float)(-TURN_SPEED * Application::getMouse()->getMousePitch() * (float)dt);
	rotationX -= pitch;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

void FPCamera::lookDown(const double dt)
{
	float pitch = (float)(-TURN_SPEED * Application::getMouse()->getMousePitch() * (float)dt);
	rotationX -= pitch;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

void FPCamera::lookUp(const double dt, float upValue)
{
	float pitch = (float)(-WALK_SPEED * Application::getMouse()->getMousePitch() * (float)dt + upValue * (float)dt);
	recoil += 5.f * (float)dt;
	rotationX -= pitch;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

void FPCamera::lookDown(const double dt, float downValue)
{
	float pitch = (float)(-WALK_SPEED * Application::getMouse()->getMousePitch() * (float)dt - downValue * (float)dt);
	recoil -= 5.f * (float)dt;;
	rotationX -= pitch;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

void FPCamera::SpinClockwise(const double dt)
{
	float angle = (float)(TURN_SPEED * (float)dt);
	view = (target - position).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(angle, 0, 0, 1);
	view = rotation * view;
	target = position + view;
}

void FPCamera::SpinCounterClockwise(const double dt)
{
	float angle = (float)(-TURN_SPEED * (float)dt);
	view = (target - position).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(angle, 0, 0, 1);
	view = rotation * view;
	target = position + view;
}

void FPCamera::Pitch(const double dt)
{
	if (Application::getMouse()->getMousePitch() > 0.0)
	{
		lookUp(dt);
	}

	else if (Application::getMouse()->getMousePitch() < 0.0)
	{
		lookDown(dt);
	}
}

void FPCamera::Yaw(const double dt)
{
	if (Application::getMouse()->getMouseYaw() > 0.0)
	{
		lookRight(dt);
	}

	else if (Application::getMouse()->getMouseYaw() < 0.0)
	{
		lookLeft(dt);
	}
}

void FPCamera::Walk(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveForward(dt, heightOffset);
	}
	else if (dt < 0)
	{
		moveBackward(abs(dt), heightOffset);
	}
}

void FPCamera::Run(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveForward(dt, heightOffset, true);
	}
	else if (dt < 0)
	{
		moveBackward(abs(dt), heightOffset, true);
	}
}

void FPCamera::Strafe(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveRight(dt, heightOffset);
	}
	else  if (dt < 0)
	{
		moveLeft(abs(dt), heightOffset);
	}
}

void FPCamera::Jump(const double dt)
{
	if (m_bJumping == false)
	{
		m_bJumping = true;

		// Calculate the jump velocity
		JumpVel = JUMPACCEL;

		if (JumpVel > JUMPMAXSPEED)
		{
			JumpVel -= JUMPMAXSPEED;
		}
	}
}

void FPCamera::Crouch(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		float diffY = (heightOffset + 10.f);

		if (position.y > diffY)
		{
			moveDown(dt, 50.f);

			if (position.y < diffY)
			{
				float posTarDiff = target.y - position.y;
				position.y = diffY;
				target.y = position.y + posTarDiff;
			}
		}
	}

	else if (dt < 0)
	{
		float diffY = (heightOffset + 20.f);

		if (position.y < diffY)
		{
			moveUp(-dt, 50.f);

			if (position.y > diffY)
			{
				float posTarDiff = target.y - position.y;
				position.y = diffY;
				target.y = position.y + posTarDiff;
			}
		}
	}
}