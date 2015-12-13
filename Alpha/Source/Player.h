#pragma once

#include "PlayerSingleton.h"

class CPlayer : public CPlayerSingleton
{
public:
	static CPlayer* GetInstance();

	//Init
	virtual void Init(Vector3 currentPos, Vector3 currentDir, Mesh* playerMesh);

	//Dir
	virtual void SetDirection(Vector3 newDirection);
	virtual void SetDirection_X(float newDir_X);
	virtual void SetDirection_Y(float newDir_Y);
	virtual void SetDirection_Z(float newDir_Z);
	virtual Vector3 GetDirection(void);

	//Angle
	virtual float GetAngle(void);
	virtual void SetAngle(float newAngle);

	//Physics
	virtual void SetGravity(float newGravity);
	virtual float GetGravity(void);
	//Jump Speed
	virtual void SetJumpSpeed(float newJSpeed);
	virtual float GetJumpSpeed(void);
	//Move Speed
	virtual void SetMoveSpeed(float newMSpeed);
	virtual float GetMoveSpeed(void);
	//Move Speed Mult
	virtual void SetMoveSpeedMult(float newMSpeedMult);
	virtual float GetMoveSpeedMult(void);

	virtual bool GetInAir(void);

	virtual SceneNode* GetNode(void);

	//Update
	virtual void Update(double dt, float CamAngle);
	virtual void UpdateMovement(double dt);

	//Game related
	virtual void SetHealth(int newHealth);
	virtual void SetLives(int newLives);
	virtual int GetHealth(void);
	virtual int GetLives(void);

private:
	CPlayer();
	~CPlayer();

	static CPlayer* instance;
};

