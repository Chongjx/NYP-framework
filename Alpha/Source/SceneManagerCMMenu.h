#ifndef SCENE_MANAGER_CM_MENU_H
#define SCENE_MANAGER_CM_MENU_H

#include "SceneManagerSelection.h"

class SceneManagerCMMenu : public SceneManagerSelection
{
public:
	SceneManagerCMMenu();
	~SceneManagerCMMenu();
	
	void Init(const int width, const int height, ResourcePool* RP);
	void Update(double dt);
	void Render();
	void Exit();

	void InitShader();
	void InitLight();

	void UpdateSelection();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
};

#endif