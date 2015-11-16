#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <map>

#include "TextTree.h"
#include "Mesh.h"

using std::map;

struct SHADER
{
	string vertexShaderDirectory = "";
	string fragmentShaderDirectory = "";
};

class ResourcePool
{
public:
	ResourcePool();
	~ResourcePool();

	void Init(string config);
	void Config();

	Mesh* retrieveMesh(string resourceName);
	string retrieveTexture(string textureName);
	Color retrieveColor(string colorName);
	SHADER retrieveShader(string shaderName);
	// Sound retrieveSound(string soundName);

	void cleanUp(void);
private:
	map<string, Mesh*> meshContainer;
	map<string, string> textureContainer;
	map<string, Color> colorContainer;
	map<string, SHADER> shaderContainer;
	// map<string, Sound> soundContanier;

	bool addMesh(string meshName, Mesh* mesh);
	bool addTexture(string textureName, string directory);
	bool addColor(string colorName, Color color);
	bool addShader(string shaderName, SHADER shader);
	// void addSound(string soundName, Sound sound);

	Branch resourceBranch;
};

#endif