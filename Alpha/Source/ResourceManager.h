#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "ResourcePool.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Init(ResourcePool* resourcePool);

	Mesh* retrieveMesh(string name);	//Get mesh from pool
	unsigned retrieveTexture(string name);	//Get texture from pool
	Color retrieveColor(string name);	//Get color from pool
	Color retrieveRandomColor(void);	//Get random color from pool
	SHADER retrieveShader(string name);		//Get shader from pool

	void DecreaseSoundEngineVolume();	//Decrease current sound engine volume by 10
	void IncreaseSoundEngineVolume();	//Increase current sound engine volume by 10
	void setSoundEngineVolume(float value);	//Set Engine volume 1 - 100
	void setListenerPosition(Vector3 position, Vector3 target);	//Sets position of listener
	void retrieveSoundas2D(string name,const bool loop = false);	//Plays 2D sound from pool
	void retrieveSoundas3D(string name,Vector3 position, const bool loop = false);	//Plays 3D sound from pool
	
private:
	ResourcePool* resourcePool;
};

#endif