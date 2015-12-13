#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject3D.h"
#include "Projectile.h"

class Weapon : public GameObject3D
{
public:
	Weapon();
	~Weapon();

	void Init(GameObject3D weapon, CProjectile type, const float RELOAD_TIME = 2.f, const float FIRE_RATE = 0.1f);	//Init all variables

	CProjectile getProjectile(void);

private:
	float RELOAD_TIME;	//Reload time
	float FIRE_RATE;	//Rate of fire

	float reload_timer;	//used to keep track
	float fire_timer;	//used to keep track

	CProjectile projectile_type;

};

#endif