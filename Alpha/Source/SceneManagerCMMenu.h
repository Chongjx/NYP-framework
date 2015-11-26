#ifndef SCENE_MANAGER_CM_MENU_H
#define SCENE_MANAGER_CM_MENU_H

#include "SceneManagerSelection.h"

class SceneManagerCMMenu : public SceneManagerSelection
{
public:
	SceneManagerCMMenu();
	~SceneManagerCMMenu();
	
	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Config();
	void Update(double dt);
	void Render();
	void Exit();

	void BindShaders();
	void InitShader();

	void RenderSelection();
	void UpdateSelection();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
};

#endif