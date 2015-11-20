#ifndef SCENE_MANAGER_CM_PLAY_H
#define SCENE_MANAGER_CM_PLAY_H

#include "SceneManagerGameplay.h"
#include "SceneNode.h"

class SceneManagerCMPlay : public SceneManagerGameplay
{
public:
	SceneManagerCMPlay();
	~SceneManagerCMPlay();

	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Update(double dt);
	void Render();
	void Exit();

	void InitShader();
	void InitLight();
	void InitCamera();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
};

#endif