#include "ResourcePool.h"

ResourcePool::ResourcePool()
{
}

ResourcePool::~ResourcePool()
{
}

void ResourcePool::AddMesh(string meshName, Mesh* mesh)
{
}

Mesh* ResourcePool::RetrieveMesh(string resourceName)
{
	map<string, Mesh*>::iterator it = meshContainer.find(resourceName);

	if (it != meshContainer.end())
	{
		return it->second;
	}

	return NULL;
}

void ResourcePool::CleanUp(void)
{
	for (map<string, Mesh*>::iterator it = meshContainer.begin(); it != meshContainer.end(); ++it)
	{
		delete it->second;
		meshContainer.erase(it);
	}
}