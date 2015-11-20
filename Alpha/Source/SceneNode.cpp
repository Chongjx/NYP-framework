#include "SceneNode.h"


SceneNode::SceneNode() : gameObject3D(NULL), parentNode(NULL)
{
}


SceneNode::~SceneNode()
{
}

void SceneNode::SetGameObject(GameObject3D *gameObject)
{
	this->gameObject3D = gameObject;
}

void SceneNode::SetParentNode(SceneNode* _parentNode)
{
	this->parentNode = _parentNode;
}

void SceneNode::AddChildNode(SceneNode *childNode)
{
	childNode->SetParentNode(this);

	this->childeNodes.push_back(childNode);
}

void SceneNode::AddChildToChildNode(string childName, SceneNode *childNode)
{
	this->GetChildNode(childName)->AddChildNode(childNode);
}

SceneNode* SceneNode::GetChildNode(string childName)
{
	for (int i = 0; i < childeNodes.size(); ++i)
	{
		if (childeNodes[i]->GetGameObject()->getName() == childName)
		{
			return childeNodes[i];
		}

		else
		{
			return childeNodes[i]->GetChildNode(childName);
		}
	}
}

GameObject3D* SceneNode::GetGameObject()
{
	return this->gameObject3D;
}