#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject3D.h"
#include "Projectile.h"

class Weapon : public GameObject3D
{
public:
	Weapon();
	~Weapon();

	void Init(GameObject3D weapon, CProjectile type, 
		const int startingAmmo = 30, const int reserveAmmo = 90,
		const float RELOAD_TIME = 2.f, const float FIRE_RATE = 0.1f);	//Init all variables

	CProjectile getProjectile(void);
	
	void Update(double dt);	//Update weapon

	int getCurrentAmmo(void);	//Get current amount of ammo

	int getReservedAmmo(void);	//Get reserved amount of ammo
	void setReservedAmmo(int value);	//Set reserved amount of ammo

	bool Fire();	//Fire Weapon
	void Reload();	//Reload Weapon
	
private:
	void RefillWeapon();	//Refill Weapon ammo

	float RELOAD_TIME;	//Reload time
	float FIRE_RATE;	//Rate of fire

	float reload_timer;	//used to keep track
	float fire_timer;	//used to keep track

	int MAX_CURRENT_AMMO;	//Maximum amount of ammo
	int Current_Ammo;	//Current amount of ammo
	int Reserve_Ammo;	//Reserved amount of ammo

	bool Reloading;	//Reloading status of weapon

	CProjectile projectile_type;

};

#endif