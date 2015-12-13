#include "Player.h"

CPlayer* CPlayer::instance = 0;

CPlayer* CPlayer::GetInstance()
{
	if (instance == 0)
		instance = new CPlayer();

	return instance;
}

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init(Vector3 currentPos, Vector3 currentDir, Mesh* playerMesh)
{
	playerNode = new SceneNode();

	GO3D_Player = new GameObject3D();
	playerNode->setActive(true);
	playerNode->SetGameObject(GO3D_Player);
	playerNode->GetGameObject()->setPosition(currentPos);
	playerNode->GetGameObject()->setMesh(playerMesh);
	playerNode->GetGameObject()->setName("Player");
	playerNode->GetGameObject()->setUpdate(true);
	playerNode->GetGameObject()->setRender(true);
	playerNode->GetGameObject()->setCollidable(true);
}

//Dir
void CPlayer::SetDirection(Vector3 newDirection)
{
	this->direction = newDirection;
}
void CPlayer::SetDirection_X(float newDir_X)
{
	this->direction.x = newDir_X;
}
void CPlayer::SetDirection_Y(float newDir_Y)
{
	this->direction.y = newDir_Y;
}
void CPlayer::SetDirection_Z(float newDir_Z)
{
	this->direction.z = newDir_Z;
}
Vector3 CPlayer::GetDirection(void)
{
	return direction;
}

//Angle
float CPlayer::GetAngle(void)
{
	return angle;
}
void CPlayer::SetAngle(float newAngle)
{
	this->angle = newAngle;
}

//Physics
void CPlayer::SetGravity(float newGravity)
{
	this->gravity = newGravity;
}
float CPlayer::GetGravity(void)
{
	return gravity;
}
void CPlayer::SetJumpSpeed(float newJSpeed)
{
	this->jumpSpeed = newJSpeed;
}
float CPlayer::GetJumpSpeed(void)
{
	return jumpSpeed;
}
void CPlayer::SetMoveSpeed(float newMSpeed)
{
	this->moveSpeed = newMSpeed;
}
float CPlayer::GetMoveSpeed(void)
{
	return moveSpeed;
}

void CPlayer::SetMoveSpeedMult(float newMSpeedMult)
{
	this->moveSpeed_Mult = newMSpeedMult;
}
float CPlayer::GetMoveSpeedMult(void)
{
	return moveSpeed_Mult;
}

bool CPlayer::GetInAir(void)
{
	return inAir;
}

SceneNode* CPlayer::GetNode(void)
{
	return playerNode;
}

//Update
void CPlayer::Update(double dt, float CamAngle)
{
	UpdateMovement(dt);
}
void CPlayer::UpdateMovement(double dt)
{
	force.x = moveSpeed * moveSpeed_Mult;
	force.z = moveSpeed * moveSpeed_Mult;

	orientation = Math::DegreeToRadian(angle);
	
	direction.x = sinf(orientation);
	direction.z = cosf(orientation);

	Vector3 acceleration = force * (1.f / mass);

	velocity.x = sinf(orientation) * acceleration.x;
	velocity.z = cosf(orientation) * acceleration.z;

	playerNode->GetGameObject()->addPosition(velocity * (float)dt);
}

//Game related
void CPlayer::SetHealth(int newHealth)
{
	this->health = newHealth;
}
void CPlayer::SetLives(int newLives)
{
	this->lives = newLives;
}
int CPlayer::GetHealth(void)
{
	return health;
}
int CPlayer::GetLives(void)
{
	return lives;
}
