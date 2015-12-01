#include "Partition.h"

Partition::Partition() :
dimension(),
id(-1),
partitionMesh(NULL)
{
	nodes.clear();
}

Partition::~Partition()
{
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
	this->nodes.clear();
}