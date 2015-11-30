#ifndef SCENE_H
#define SCENE_H

#include "ResourceManager.h"
#include "InputManager.h"
#include "ProjectileManager.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls) = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif