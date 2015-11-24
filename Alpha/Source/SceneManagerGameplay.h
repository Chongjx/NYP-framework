#ifndef SCENE_MANAGER_GAMEPLAY_H
#define SCENE_MANAGER_GAMEPLAY_H

#include "SceneManager.h"

#include "Fog.h"

class SceneManagerGameplay : public SceneManager
{
public:
	SceneManagerGameplay() {}
	virtual ~SceneManagerGameplay() {}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
	{
		SceneManager::Init(width, height, RP, controls);
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

	virtual void BindShaders() 
	{
		SceneManager::BindShaders();
	}

	virtual void InitShader() {}
	virtual void InitLight() {}

	virtual void RenderLight() {}
	virtual void RenderBG() {}
	virtual void RenderStaticObject() {}
	virtual void RenderMobileObject() {}
};

#endif