#ifndef SCENE_MANAGER_CM_PLAY_H
#define SCENE_MANAGER_CM_PLAY_H

#include "SceneManagerGameplay.h"
#include "SceneNode.h"

class SceneManagerCMPlay : public SceneManagerGameplay
{
private:
	vector<GameObject3D*> objectList;
	SceneNode* sceneGraph;
public:
	SceneManagerCMPlay();
	~SceneManagerCMPlay();

	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Config();
	void Update(double dt);
	void Render();
	void Exit();

	void BindShaders();
	void InitShader();

	void InitSceneGraph();
	void FSMApplication();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
};

#endif