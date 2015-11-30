#ifndef CPROJECTILE_H
#define CPROJECTILE_H

#include "Vector3.h"
#include "GameObject3D.h"

class CProjectile : public GameObject3D
{
public:
	CProjectile(void);
	~CProjectile(void);

	void Update(const double dt);	//Update status

	void Init(Vector3 newPosition, Vector3 newDirection, bool active, float speed, Mesh* mesh);	//Initialize

	Vector3 GetDirection(void);	//Get direction of projectile

private:
	Vector3 m_v2Direction;	// The direction of the projectile

	float m_fSpeed;	// Speed
};

#endif