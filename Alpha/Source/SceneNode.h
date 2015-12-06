#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "GameObject3D.h"

class SceneManager;

class SceneNode
{
public:
	SceneNode();
	~SceneNode();
	
	void SetGameObject(GameObject3D *gameObject);
	void SetParentNode(SceneNode* _parentNode);

	void AddChildNode(SceneNode *childNode);
	void AddChildToChildNode(string childName, SceneNode *childNode);

	void Draw(SceneManager *sceneManager);
	void DrawChild(SceneManager *sceneManager);

	SceneNode* GetParentNode(void);

	void CleanUp();

	bool HasChild(void);

	SceneNode* GetChildNode(string childName);
	
	GameObject3D* GetGameObject();

	vector<SceneNode*> childNodes;
	SceneNode *parentNode;
protected:
	GameObject3D* gameObject3D;
	
};

#endif