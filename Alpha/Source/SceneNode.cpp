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

void SceneNode::Draw(SceneManager *sceneManager)
{
	sceneManager->PreRender(true);
	sceneManager->RenderPush(gameObject3D->getProperties().modelProperties);
	gameObject3D->getMesh()->Render();

	for (int i = 0; i < childNodes.size(); ++i)
	{
		this->childNodes[i]->DrawChild(sceneManager);
	}

	sceneManager->RenderPop();
}

void SceneNode::DrawChild(SceneManager *sceneManager)
{
	sceneManager->RenderPush(gameObject3D->getProperties().modelProperties);
	gameObject3D->getMesh()->Render();

	for (int i = 0; i < childNodes.size(); ++i)
	{
		this->childNodes[i]->DrawChild(sceneManager);
	}

	sceneManager->RenderPop();
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
}

GameObject3D* SceneNode::GetGameObject()
{
	return this->gameObject3D;
}