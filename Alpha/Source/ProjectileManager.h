#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <vector>
#include "Projectile.h"

using std::vector;

class SceneManager;

class ProjectileManager
{
public:
	ProjectileManager(void);
	~ProjectileManager(void);

	void FetchProjectile(Vector3 position, Vector3 direction,float speed, Mesh* mesh);	//Add new projectile
	void RemoveProjectile(CProjectile* projectile);	//Remove projectile

	int GetNumberOfActiveProjectiles(void);	//Get active projectile count

	void Update(const double dt);	//Update 
	void Draw(SceneManager *sceneManager);	//Render

private:
	int m_iActiveProjectileCount;	//Current active projectiles

	Vector3 Boundary_TopLeft, Boundary_BottomRight;

	const unsigned m_iStartProjectileCount = 100;	//Starting number of projectiles
	vector<CProjectile*> m_ProjectileList;	//List containing all projectiles
};

#endif
