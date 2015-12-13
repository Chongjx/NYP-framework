#include "Weapon.h"

Weapon::Weapon() :
	RELOAD_TIME(0.f),
	FIRE_RATE(0.f),
	reload_timer(0.f),
	fire_timer(0.f)
{

}

Weapon::~Weapon()
{

}

void Weapon::Init(GameObject3D weapon, CProjectile type, const float RELOAD_TIME, const float FIRE_RATE)
{
	this->setPosition(weapon.getPosition());
	this->setCollidable(weapon.getCollidable());
	this->setMesh(weapon.getMesh());
	this->setName(weapon.getName());
	this->setHitbox(weapon.getHitbox());
	this->setReflectLight(weapon.getReflectLight());

	this->projectile_type = type;

	this->RELOAD_TIME = RELOAD_TIME;
	this->FIRE_RATE = FIRE_RATE;
}

CProjectile Weapon::getProjectile(void)
{
	return this->projectile_type;
}