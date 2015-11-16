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
	return resourcePool->retrieveMesh(name);
}

string ResourceManager::retrieveTexture(string name)
{
	return resourcePool->retrieveTexture(name);
}

Color ResourceManager::retrieveColor(string name)
{
	return resourcePool->retrieveColor(name);
}