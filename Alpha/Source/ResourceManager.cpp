#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Init(ResourcePool* resourcePool)
{
	this->resourcePool = resourcePool;
}

Mesh* ResourceManager::retrieveMesh(string name)
{
	return resourcePool->RetrieveMesh(name);
}

string ResourceManager::retrieveTexture(string name)
{
	return resourcePool->RetrieveTexture(name);
}

Color ResourceManager::retrieveColor(string name)
{
	return resourcePool->RetrieveColor(name);
}