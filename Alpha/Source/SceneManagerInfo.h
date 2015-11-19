#ifndef SCENE_MANAGER_INFO_H
#define SCENE_MANAGER_INFO_H

#include "SceneManager.h"

class SceneManagerInfo : public SceneManager
{
protected:
	vector<Button2D> interactiveButtons;
public:
	SceneManagerInfo() {}
	virtual ~SceneManagerInfo() {}

	virtual void Init(const int width, const int height, ResourcePool* RP)
	{
		SceneManager::Init(width, height, RP);

		interactiveButtons.clear();
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
		interactiveButtons.clear();

		SceneManager::Exit();
	}

	virtual void InitShader() {}
	virtual void RenderLight() {}
};

#endif