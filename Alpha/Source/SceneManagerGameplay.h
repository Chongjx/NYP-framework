#ifndef SCENE_MANAGER_GAMEPLAY_H
#define SCENE_MANAGER_GAMEPLAY_H

#include "SceneManager.h"

#include "Fog.h"

class SceneManagerGameplay : public SceneManager
{
public:
	SceneManagerGameplay() {}
	virtual ~SceneManagerGameplay() {}

	virtual void Init(const int width, const int height, ResourcePool* RP)
	{
		SceneManager::Init(width, height, RP);
	}

	virtual void Update(double dt)
	{
		SceneManager::Update(dt);
	}

	virtual void Render()
	{
		SceneManager::Render();
	}

	virtual void Exit()
	{
		SceneManager::Exit();
	}

	virtual void InitShader() {}
	virtual void RenderLight() {}
};

#endif