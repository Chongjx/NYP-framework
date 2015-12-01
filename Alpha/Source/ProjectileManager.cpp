#include "ProjectileManager.h"
#include "SceneManager.h"

/********************************************************************************
 Constructor
 ********************************************************************************/
ProjectileManager::ProjectileManager(void) :
	m_iActiveProjectileCount(0)
{
	//Create projectiles
	for (unsigned i = 0; i < m_iStartProjectileCount; ++i)
	{
		m_ProjectileList.push_back(new CProjectile());
	}

	Boundary_TopLeft		= Vector3( 300.0f, 300.0f, 300.0f);
	Boundary_BottomRight	= Vector3( -300.0f, 0.0f, -300.0f);
}

/********************************************************************************
 Destructor
 ********************************************************************************/
ProjectileManager::~ProjectileManager(void)
{
	CleanUp();
}

/********************************************************************************
Use a non-active projectile
********************************************************************************/
void ProjectileManager::FetchProjectile(Vector3 position, Vector3 direction, float speed, Mesh* mesh)
{
	for (std::vector<CProjectile*>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); ++it)
	{
		CProjectile* newProjectile = (CProjectile *)*it;
		//Get first non active projectile to use
		if (!newProjectile->getUpdate())
		{
			newProjectile->Init(position, direction, true, speed, mesh);
			break;
		}
	}
	//If all existing projectiles are active, create more projectiles
	for (unsigned i = 0; i < 10; ++i)
	{
		m_ProjectileList.push_back(new CProjectile());
	}
	//Use newly created projectile
	CProjectile* newProjectile = m_ProjectileList.back();
	newProjectile->Init(position, direction, true, speed,mesh);
}

/********************************************************************************
 Remove Projectile
 ********************************************************************************/
void ProjectileManager::RemoveProjectile(CProjectile* projectile)
{
	projectile->setUpdate(false);
	projectile->setRender(false);
	this->m_iActiveProjectileCount--;
}

/********************************************************************************
 Get Number of Active Projectile
 ********************************************************************************/
int ProjectileManager::GetNumberOfActiveProjectiles(void)
{
	return this->m_iActiveProjectileCount;
}

/********************************************************************************
 Update
 ********************************************************************************/
void ProjectileManager::Update(const double dt)
{
	//Iterate through vector of projectiles
	for (std::vector<CProjectile*>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); ++it)
	{
		CProjectile* projectile = (CProjectile *)*it;
		
		//Only update if projectile is active
		if (projectile->getUpdate())
		{
			projectile->Update(dt);
		}
	}
}

/********************************************************************************
Render projectile
********************************************************************************/
void ProjectileManager::Draw(SceneManager *sceneManager)
{
	for (std::vector<CProjectile*>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); ++it)
	{
		CProjectile* projectile = (CProjectile *)*it;

		//Only render active projectiles
		if (projectile->getRender())
		{
			sceneManager->RenderPush(projectile->getProperties().modelProperties);
			sceneManager->Render3DMesh(projectile->getMesh(),false);
			sceneManager->RenderPop();
		}
	}
}

/********************************************************************************
Clean up
********************************************************************************/
void ProjectileManager::CleanUp()
{
	//Cleaning up vector
	while (m_ProjectileList.size() > 0)
	{
		CProjectile* temp = m_ProjectileList.back();
		delete temp;
		m_ProjectileList.pop_back();
	}
}