#ifndef SCENE_MANAGER_TRANSITION_H
#define SCENE_MANAGER_TRANSITION_H

#include "SceneManager.h"

class SceneManagerTransition : public SceneManager
{
protected:
	bool run;
	bool repeat;
	int repeatCount;
	int runCount;
	bool complete;
	bool shldExit;
public:

	SceneManagerTransition() {}
	virtual ~SceneManagerTransition() {}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
	{
		SceneManager::Init(width, height, RP, controls);

		this->run = true;
		this->repeat = false;
		this->repeatCount = 0;
		this->runCount = 0;
		this->complete = false;
		this->shldExit = false;
	}

	virtual void Config() {}

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
	virtual void RenderTransition() {}
};

#endif