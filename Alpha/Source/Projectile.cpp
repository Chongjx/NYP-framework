#include "Projectile.h"

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectile::CProjectile(void)
: m_v2Direction(0, 0, 0)
, m_fSpeed(0.0f)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectile::~CProjectile(void)
{
}


/********************************************************************************
Initialize new variables for projectile
********************************************************************************/
void CProjectile::Init(Vector3 newPosition, Vector3 newDirection, bool active, float speed, Mesh* mesh)
{
	this->setPosition(newPosition);
	this->m_v2Direction = newDirection;
	this->setUpdate(active);
	this->setRender(active);
	this->m_fSpeed = speed;
	this->setMesh(mesh);
}

/********************************************************************************
 Update the status of this projectile
 ********************************************************************************/
void CProjectile::Update(const double dt)
{
	//Updating position
	this->setPosition(this->position += m_v2Direction * (float)dt * m_fSpeed);
}

/********************************************************************************
 Get the direction of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetDirection(void)
{
	return m_v2Direction;
}