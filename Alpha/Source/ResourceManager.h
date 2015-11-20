#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "ResourcePool.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Init(ResourcePool* resourcePool);

	Mesh* retrieveMesh(string name);
	unsigned retrieveTexture(string name);
	Color retrieveColor(string name);
	SHADER retrieveShader(string name);
	void retrieveSound(string name);
	
private:
	ResourcePool* resourcePool;
};

#endif