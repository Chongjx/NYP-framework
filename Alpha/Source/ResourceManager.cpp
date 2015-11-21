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

unsigned ResourceManager::retrieveTexture(string name)
{
	return resourcePool->retrieveTexture(name);
}

Color ResourceManager::retrieveColor(string name)
{
	return resourcePool->retrieveColor(name);
}

Color ResourceManager::retrieveRandomColor(void)
{
	return resourcePool->retrieveRandomColor();
}

SHADER ResourceManager::retrieveShader(string name)
{
	return resourcePool->retrieveShader(name);
}

void ResourceManager::retrieveSound(string name)
{
	resourcePool->soundPool->retrieveSound(name);
}