#pragma once

#include <windows.h>

#include "SceneNode.h"
#include "Vector3.h"
#include "Mesh.h"
#include "TPCamera.h"

#define Player CPlayer::GetInstance()

class CPlayerSingleton : public SceneNode
{
public:
	CPlayerSingleton();
	~CPlayerSingleton();

	//Init
	virtual void Init(Vector3 currentPos, Vector3 currentDir, Mesh* playerMesh) = 0;

	//Dir
	virtual void SetDirection(Vector3 newDirection) = 0;
	virtual void SetDirection_X(float newDir_X) = 0;
	virtual void SetDirection_Y(float newDir_Y) = 0;
	virtual void SetDirection_Z(float newDir_Z) = 0;
	virtual Vector3 GetDirection(void) = 0;

	//Angle
	virtual float GetAngle(void) = 0;
	virtual void SetAngle(float newAngle) = 0;

	//Physics
	virtual void SetGravity(float newGravity) = 0;
	virtual float GetGravity(void) = 0;
	//Jump Speed
	virtual void SetJumpSpeed(float newJSpeed) = 0;
	virtual float GetJumpSpeed(void) = 0;
	//Move Speed
	virtual void SetMoveSpeed(float newMSpeed) = 0;
	virtual float GetMoveSpeed(void) = 0;
	//Move Speed Mult
	virtual void SetMoveSpeedMult(float newMSpeedMult) = 0;
	virtual float GetMoveSpeedMult(void) = 0;

	virtual bool GetInAir(void) = 0;

	virtual SceneNode* GetNode(void) = 0;

	//Update
	virtual void Update(double dt, float CamAngle) = 0;
	virtual void UpdateMovement(double dt) = 0;

	//Game related
	virtual void SetHealth(int newHealth) = 0;
	virtual void SetLives(int newLives) = 0;
	virtual int GetHealth(void) = 0;
	virtual int GetLives(void) = 0;

protected:
	SceneNode* playerNode;
	GameObject3D* GO3D_Player;

	Vector3 force;
	Vector3 velocity;
	Vector3 direction;

	int health;
	int lives;
	float mass;
	float angle;
	float moveSpeed;
	float jumpSpeed;
	float gravity;
	float orientation;
	float moveSpeed_Mult;
	bool inAir;
};

