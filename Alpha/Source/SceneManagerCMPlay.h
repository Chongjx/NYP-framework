#ifndef SCENE_MANAGER_CM_PLAY_H
#define SCENE_MANAGER_CM_PLAY_H

#include "SceneManagerGameplay.h"

class SceneManagerCMPlay : public SceneManagerGameplay
{
private:
	vector<GameObject3D*> objectList;
	SceneNode* sceneGraph;
	SceneNode* staticSceneGraph;
	SceneNode* dynamicSceneGraph;
	SpatialPartitionManager* spatialPartitionManager;
	// MiniMap* miniMap;

	Vector3 worldStart;
	Vector3 worldEnd;

	Mesh* textMesh;
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

	void InitPartition();
	void InitSceneGraph();
	void FSMApplication();

	void UpdateMouse();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
	void RenderGUI();
};

#endif