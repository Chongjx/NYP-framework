#ifndef SCENE_MANAGER_SELECTION_H
#define SCENE_MANAGER_SELECTION_H

#include "SceneManager.h"

class SceneManagerSelection : public SceneManager
{
public:
	vector<Button2D> interactiveButtons;

public:
	SceneManagerSelection() {}
	virtual ~SceneManagerSelection() {}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
	{
		SceneManager::Init(width, height, RP, controls);

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
	virtual void InitLight() {}

	virtual void RenderLight() {}
	virtual void RenderBG() {}
	virtual void RenderStaticObject() {}
	virtual void RenderMobileObject() {}

	virtual void UpdateSelection() {}
};

#endif