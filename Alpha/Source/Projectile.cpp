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
void CProjectile::Init(GameObject3D object, Vector3 newDirection, bool active, float speed)
{
	this->setPosition(object.getPosition());
	this->setCollidable(object.getCollidable());
	this->setMesh(object.getMesh());
	this->setName(object.getName());
	this->setHitbox(object.getHitbox());
	this->setReflectLight(object.getReflectLight());

	this->m_v2Direction = newDirection;
	this->m_fSpeed = speed;
	this->setUpdate(active);
	this->setRender(active);
}

/********************************************************************************
 Update the status of this projectile
 ********************************************************************************/
void CProjectile::Update(const double dt)
{
	//Updating position & hitbox
	this->setPosition(this->position += m_v2Direction * (float)dt * m_fSpeed);
	this->updateHitbox();
}

/********************************************************************************
 Get the direction of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetDirection(void)
{
	return m_v2Direction;
}

GameObject3D* CProjectile::getGameObject(void)
{
	return this;
}