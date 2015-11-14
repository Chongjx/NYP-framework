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

	void AddTexture(string textureName, string directory);
	string RetrieveTexture(string textureName);

	void AddColor(string colorName, Color color);
	Color RetrieveColor(string colorName);

	// void AddSound(string soundName, Sound sound);
	// Sound RetrieveSound(string soundName);

	void CleanUp(void);
private:
	map<string, Mesh*> meshContainer;
	map<string, string> textureContainer;
	map<string, Color> colorContainer;
	// map<string, Sound> soundContanier;
};

#endif