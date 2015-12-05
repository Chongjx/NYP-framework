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
	//if (this->nodes)
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
}

void Partition::Render(void)
{
}

void Partition::RenderObjects(const int resolution)
{
}

void Partition::Update(void)
{
}

void Partition::CleanUp(void)
{
	// release all the handle of the nodes in the partition only
	// let sceneManager delete all the nodes
	this->nodes.clear();
}