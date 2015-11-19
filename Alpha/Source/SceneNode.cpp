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

	this->childNodes.push_back(childNode);
}

void SceneNode::AddChildToChildNode(string childName, SceneNode *childNode)
{
	this->GetChildNode(childName)->AddChildNode(childNode);
}

SceneNode* SceneNode::GetChildNode(string childName)
{
	SceneNode *resultNode;

	for (int i = 0; i < childNodes.size(); ++i)
	{
		if (childNodes[i]->GetGameObject()->getName() == childName)
		{
			return childNodes[i];
		}

		else if (childNodes[i]->childNodes.size() > 0)
		{
			resultNode = childNodes[i]->GetChildNode(childName);

			if (resultNode != NULL)
			{
				return resultNode;
			}
		}
	}

	return NULL;
}

GameObject3D* SceneNode::GetGameObject()
{
	return this->gameObject3D;
}