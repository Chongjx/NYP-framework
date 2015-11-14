#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Mtx44.h"
#include "FPCamera.h"
#include "TPCamera.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Fog.h"

struct KEYS
{
	std::string name;
	int value;
	bool pressed;
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

protected:
	unsigned vertexArrayID;
	unsigned programID;
	vector<unsigned> parameters;

	FPCamera fpCamera;
	TPCamera tpCamera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	vector<Light> lights;

	bool lightEnabled;
	float fps;
};

#endif