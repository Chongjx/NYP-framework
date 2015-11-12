#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <map>

#include "Mesh.h"

using std::map;

class ResourcePool
{
public:
	ResourcePool();
	~ResourcePool();

	void AddMesh(string meshName, Mesh* mesh);
	Mesh* RetrieveMesh(string resourceName);

	void CleanUp(void);
private:
	map<string, Mesh*> meshContainer;
};

#endif