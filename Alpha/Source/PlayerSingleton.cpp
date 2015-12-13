#include "PlayerSingleton.h"

CPlayerSingleton::CPlayerSingleton()
: playerNode(NULL)
, GO3D_Player(NULL)
, health(0)
, lives(0)
, mass(1.f)
, angle(0.f)
, moveSpeed(10.f)
, jumpSpeed(10.f)
, gravity(9.8f)
, orientation(0.f)
, moveSpeed_Mult(1.f)
, inAir(false)
{
}


CPlayerSingleton::~CPlayerSingleton()
{
}