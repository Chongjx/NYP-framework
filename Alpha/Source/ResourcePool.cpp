#include "ResourcePool.h"

ResourcePool::ResourcePool()
{
}

ResourcePool::~ResourcePool()
{
}

bool ResourcePool::AddMesh(string meshName, Mesh* mesh)
{
	map<string, Mesh*>::iterator it = meshContainer.find(meshName);

	// If a mesh of the same name is found
	if (it != meshContainer.end())
	{
		return false;
	}

	else
	{
		meshContainer.insert(std::pair<string, Mesh*>(meshName, mesh));

		return true;
	}
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

bool ResourcePool::AddTexture(string textureName, string directory)
{
	map<string, string>::iterator it = textureContainer.find(textureName);

	// If a mesh of the same name is found
	if (it != textureContainer.end())
	{
		return false;
	}

	else
	{
		textureContainer.insert(std::pair<string, string>(textureName, directory));

		return true;
	}
}

string ResourcePool::RetrieveTexture(string textureName)
{
	map<string, string>::iterator it = textureContainer.find(textureName);

	if (it != textureContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::AddColor(string colorName, Color color)
{
	map<string, Color>::iterator it = colorContainer.find(colorName);

	// If a mesh of the same name is found
	if (it != colorContainer.end())
	{
		return false;
	}

	else
	{
		colorContainer.insert(std::pair<string, Color>(colorName, color));

		return true;
	}
}

Color ResourcePool::RetrieveColor(string colorName)
{
	map<string, Color>::iterator it = colorContainer.find(colorName);

	if (it != colorContainer.end())
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