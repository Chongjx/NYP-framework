#include "Partition.h"

Partition::Partition() :
dimension(),
id(-1),
partitionMesh(NULL)
{
	// clean up the node before start
	this->CleanUp();
}

Partition::~Partition()
{
	// release all the handle of the nodes in the partition only
	// let sceneManager delete all the nodes
	nodes.clear();
}

void Partition::Init(Vector3 dimension, int id)
{
	this->dimension = dimension;
	this->id = id;
}

void Partition::Init(Vector3 dimension, int id, Mesh* mesh)
{
	this->dimension = dimension;
	this->id = id;
	this->partitionMesh = mesh;
}

void Partition::Init(Vector3 dimension, Vector3 minPosition, Vector3 maxPosition, int id, Mesh* mesh)
{
	this->dimension = dimension;
	this->minPosition = minPosition;
	this->maxPosition = maxPosition;
	this->id = id;
	this->partitionMesh = mesh;
}

void Partition::setMesh(Mesh* mesh)
{
	this->partitionMesh = mesh;
}

void Partition::addNode(SceneNode* node)
{
	bool exist = false;
	// ensure the vector does not contain this node
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		if (nodes[i] == node)
		{
			exist = true;
			break;
		}
	}

	if (!exist)
	{
		nodes.push_back(node);
	}
}

void Partition::removeNode(SceneNode* node)
{
	for (vector<SceneNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		SceneNode* temp = *(it);

		if (temp == node)
		{
			it = nodes.erase(it);
			break;
		}
	}
}

vector<SceneNode*> Partition::getNodes(void)
{
	return this->nodes;
}

Mesh* Partition::getMesh(void)
{
	return this->partitionMesh;
}

void Partition::deleteObjects(void)
{
	nodes.clear();
}

void Partition::Render(void)
{
}

void Partition::RenderObjects(const int resolution)
{
}

void Partition::Update(void)
{
	// release all the handle of the nodes in the partition only
	// let sceneManager delete all the nodes
	for (vector<SceneNode*>::iterator it = nodes.begin(); it != nodes.end();)
	{
		SceneNode* temp = *(it);

		if (temp->nodeType == SceneNode::DYNAMIC_NODE)
		{
			it = nodes.erase(it);
		}

		else
		{
			++it;
		}
	}
}

void Partition::CleanUp(void)
{
	nodes.clear();
}