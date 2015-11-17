#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Mtx44.h"
#include "FPCamera.h"
#include "TPCamera.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Fog.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "SoundManager.h"

struct KEYS
{
	std::string name;
	int value;
	bool pressed;
};

class SceneManager : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	SceneManager();
	~SceneManager();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

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

	ResourceManager resourceManager;
	InputManager inputManager;
	SoundManager soundManager;

	bool lightEnabled;
	float fps;
};

#endif