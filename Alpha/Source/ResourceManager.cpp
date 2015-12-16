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

void ResourceManager::DecreaseSoundEngineVolume()
{
	resourcePool->soundPool->DecreaseEngineVolume();
}
void ResourceManager::IncreaseSoundEngineVolume()
{
	resourcePool->soundPool->IncreaseEngineVolume();
}

void ResourceManager::setSoundEngineVolume(float value)
{
	resourcePool->soundPool->setEngineVolume(value);
}
void ResourceManager::setListenerPosition(Vector3 position, Vector3 target)
{
	resourcePool->soundPool->setListenerPos(position, target);
}

void ResourceManager::retrieveSoundas2D(string name,bool playNew, bool loop)
{
	resourcePool->soundPool->retrieveSound2D(name,playNew, loop);
}
void ResourceManager::retrieveSoundas3D(string name, Vector3 position, bool playNew, bool loop)
{
	resourcePool->soundPool->retrieveSound3D(name, position,playNew, loop);
}
void ResourceManager::stopAllSounds(void)
{
	resourcePool->soundPool->stopAllSound();
}