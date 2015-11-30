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

	void UpdateMouse();
	void UpdateSelection();
	void RenderSelection();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();

private:
	SpriteAnimation* fireball;
};

#endif