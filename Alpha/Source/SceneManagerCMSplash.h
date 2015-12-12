#ifndef SCENE_MANAGER_CM_SPLASH_H
#define SCENE_MANAGER_CM_SPLASH_H

#include "SceneManagerTransition.h"

class SceneManagerCMSplash : public SceneManagerTransition
{
private:
	Mesh* splashTexture;
	Vector2 textureScale;
	float pauseTimer;
	bool startTransition;
	float splashTimer;
	
public:
	SceneManagerCMSplash();
	~SceneManagerCMSplash();

	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Config();
	void Update(double dt);
	void Render();
	void Exit();

	void InitShader();
	void BindShaders();

	void UpdateMouse();
	void UpdateTransition(double dt);

	void RenderLight();
	void RenderTransition();
};

#endif