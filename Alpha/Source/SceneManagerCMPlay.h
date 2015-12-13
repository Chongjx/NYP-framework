#ifndef SCENE_MANAGER_CM_PLAY_H
#define SCENE_MANAGER_CM_PLAY_H

#include "SceneManagerGameplay.h"
#include "Player.h"

class SceneManagerCMPlay : public SceneManagerGameplay
{
private:
	vector<SceneNode*> nodeList;
	SpatialPartitionManager* spatialPartitionManager;
	SceneNode* sceneGraph;
	SceneNode* staticSceneGraph;
	SceneNode* dynamicSceneGraph;
	// MiniMap* miniMap;

	GameObject3D testProjectile;

	Mesh* textMesh;
public:
	SceneManagerCMPlay();
	~SceneManagerCMPlay();

	void Init(const int width, const int height, ResourcePool* RP, InputManager* controls);
	void Config();
	void Config(string directory);
	void Update(double dt);
	void Render();
	void Exit();

	void InitShader();
	void BindShaders();

	void InitSceneGraph();
	void FSMApplication();

	void UpdateMouse();

	void RenderLight();
	void RenderBG();
	void RenderStaticObject();
	void RenderMobileObject();
	void RenderGUI();

	SceneNode* getNode(void);
	CPlayer* player;
};

#endif