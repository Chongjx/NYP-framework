#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <map>

#include "TextTree.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MeshBuilder.h"

using std::map;

void static stringToVector(string text, Vector2 &vec)
{
	int lastContinue = 0;
	string xValue;
	string yValue;

	for (int position = 0; position < 2; ++position)
	{
		for (unsigned j = lastContinue; j < text.size() && text[j] != ','; ++j)
		{
			if (position == 0)
			{
				xValue += text[j];
			}

			else if (position == 1)
			{
				yValue += text[j];
			}

			lastContinue = j + 2;
		}
	}

	vec.Set(stof(xValue), stof(yValue));
}

void static stringToVector(string text, Vector3 &vec)
{
	int lastContinue = 0;
	string xValue;
	string yValue;
	string zValue;

	for (int position = 0; position < 3; ++position)
	{
		for (unsigned j = lastContinue; j < text.size() && text[j] != ','; ++j)
		{
			if (position == 0)
			{
				xValue += text[j];
			}

			else if (position == 1)
			{
				yValue += text[j];
			}

			else
			{
				zValue += text[j];
			}

			lastContinue = j + 2;
		}
	}

	vec.Set(stof(xValue), stof(yValue), stof(zValue));
}

void static stringToBool(string text, bool &boo)
{
	if (text == "True" || text == "1" || text == "true")
	{
		boo = true;
	}
	else
	{
		boo = false;
	}
}

struct SHADER
{
	string name = "";
	string vertexShaderDirectory = "";
	string fragmentShaderDirectory = "";
};

struct HEIGHTMAP
{
	vector <unsigned char> heightMap;
	string name = "";
};

struct SOUND
{
	string name = "";
	string soundDirectory = "";
};

class ResourcePool
{
public:
	ResourcePool();
	~ResourcePool();

	void Init(string config);
	void Config();

	Mesh* retrieveMesh(string resourceName);
	unsigned retrieveTexture(string textureName);
	Color retrieveColor(string colorName);
	SHADER retrieveShader(string shaderName);
	HEIGHTMAP retrieveHeightmap(string heightmapName);
	SOUND retrieveSound(string soundName);

	void cleanUp(void);
private:
	map<string, Mesh*> meshContainer;
	map<string, unsigned> textureContainer;
	map<string, Color> colorContainer;
	map<string, SHADER> shaderContainer;
	map<string, HEIGHTMAP> heightmapContainer;
	map<string, SOUND> soundContainer;

	void processMesh(string config);
	void processTexture(string config);
	void processColor(string config);
	void processShader(string config);
	void processSound(string config);

	bool addMesh(string meshName, Mesh* mesh);
	bool addTexture(string textureName, string directory);
	bool addColor(string colorName, Color color);
	bool addShader(string shaderName, SHADER shader);
	bool addHeightmap(string heightmapName, HEIGHTMAP heightmap);
	bool addSound(string soundName, SOUND sound);

	Branch resourceBranch;
};

#endif