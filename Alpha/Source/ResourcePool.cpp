#include "ResourcePool.h"

ResourcePool::ResourcePool()
{
}

ResourcePool::~ResourcePool()
{
}

void ResourcePool::Init(string config)
{
	resourceBranch = TextTree::FileToRead(config);

	Config();
}

void ResourcePool::Config()
{
	/*for (vector<Branch>::iterator branch = resourceBranch.childBranches.begin(); branch != resourceBranch.childBranches.end(); ++branch)
	{
		/*if (branch->branchName == "SetUp")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "currentPos")
				{
					string xCoord;
					string yCoord;
					int lastContinue = 0;
					for (unsigned j = 0; j < attriValue.size() && attriValue[j] != ','; ++j)
					{
						xCoord += attriValue[j];
						lastContinue = j + 2;
					}

					for (unsigned j = lastContinue; j < attriValue.size(); ++j)
					{
						yCoord += attriValue[j];
					}

					this->currentPosX = stoi(xCoord);
					this->currentPosY = stoi(yCoord);
				}

				else if (attriName == "sensitivity")
				{
					this->sensitivity = stof(attriValue);
				}
			}
		}
	}*/
}

bool ResourcePool::addMesh(string meshName, Mesh* mesh)
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

Mesh* ResourcePool::retrieveMesh(string resourceName)
{
	map<string, Mesh*>::iterator it = meshContainer.find(resourceName);

	if (it != meshContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addTexture(string textureName, string directory)
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

string ResourcePool::retrieveTexture(string textureName)
{
	map<string, string>::iterator it = textureContainer.find(textureName);

	if (it != textureContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addColor(string colorName, Color color)
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

Color ResourcePool::retrieveColor(string colorName)
{
	map<string, Color>::iterator it = colorContainer.find(colorName);

	if (it != colorContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addShader(string shaderName, SHADER shader)
{
	map<string, SHADER>::iterator it = shaderContainer.find(shaderName);

	// If a mesh of the same name is found
	if (it != shaderContainer.end())
	{
		return false;
	}

	else
	{
		shaderContainer.insert(std::pair<string, SHADER>(shaderName, shader));

		return true;
	}
}

SHADER ResourcePool::retrieveShader(string shaderName)
{
	map<string, SHADER>::iterator it = shaderContainer.find(shaderName);

	if (it != shaderContainer.end())
	{
		return it->second;
	}

	return SHADER();
}

void ResourcePool::cleanUp(void)
{
	for (map<string, Mesh*>::iterator it = meshContainer.begin(); it != meshContainer.end(); ++it)
	{
		delete it->second;
		meshContainer.erase(it);
	}
}