#include "Weapon.h"

Weapon::Weapon() :
	RELOAD_TIME(0.f),
	FIRE_RATE(0.f),
	reload_timer(0.f),
	fire_timer(0.f),
	Current_Ammo(0),
	Reserve_Ammo(0),
	Reloading(false),
	MAX_CURRENT_AMMO(0)
{

}

Weapon::~Weapon()
{

}

void Weapon::Init(GameObject3D weapon, CProjectile type, 
	const int startingAmmo, const int reserveAmmo,
	const float RELOAD_TIME, const float FIRE_RATE)
{
	this->setPosition(weapon.getPosition());
	this->setCollidable(weapon.getCollidable());
	this->setMesh(weapon.getMesh());
	this->setName(weapon.getName());
	this->setHitbox(weapon.getHitbox());
	this->setReflectLight(weapon.getReflectLight());

	this->projectile_type = type;

	this->MAX_CURRENT_AMMO = startingAmmo;
	this->Current_Ammo = startingAmmo;
	this->Reserve_Ammo = reserveAmmo;

	this->RELOAD_TIME = RELOAD_TIME;
	this->FIRE_RATE = FIRE_RATE;
}

void Weapon::Update(double dt)
{
	this->fire_timer += (float)dt;

	//Only if reloading weapon
	if (Reloading){
		this->reload_timer += (float)dt;
		if (reload_timer >= RELOAD_TIME){
			reload_timer = 0.f;
			RefillWeapon();
			Reloading = false;
		}
	}
}

CProjectile Weapon::getProjectile(void)
{
	return this->projectile_type;
}

int Weapon::getCurrentAmmo(void)
{
	return this->Current_Ammo;
}

int Weapon::getReservedAmmo(void)
{
	return this->Reserve_Ammo;
}
void Weapon::setReservedAmmo(int value)
{
	this->Reserve_Ammo = value;
}

void Weapon::RefillWeapon()
{
	unsigned difference = MAX_CURRENT_AMMO - Current_Ammo;

	if (difference <= Reserve_Ammo)
	{
		Reserve_Ammo -= difference;
		Current_Ammo += difference;
	}
	if (difference > Reserve_Ammo)
	{
		Current_Ammo += Reserve_Ammo;
		Reserve_Ammo = 0;
	}
}

bool Weapon::Fire()
{
	if (this->fire_timer >= FIRE_RATE && !Reloading)
	{
		this->fire_timer = 0.f;
		return true;
	}
	return false;
}

void Weapon::Reload()
{
	if (Current_Ammo < MAX_CURRENT_AMMO && Reserve_Ammo > 0){
		this->Reloading = true;
	}
}