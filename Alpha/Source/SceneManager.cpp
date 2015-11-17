#include "SceneManager.h"
#include "GL\glew.h"

#include "shader.hpp"
SceneManager::SceneManager()
{
	parameters.clear();
	lights.clear();
	lightEnabled = true;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//Loading of Shaders
	//programID = LoadShaders(resourceManager.retrieveShader("comg").vertexShaderDirectory.c_str(), resourceManager.retrieveShader("comg").fragmentShaderDirectory.c_str());
}

void SceneManager::Update(double dt)
{

}

void SceneManager::Render()
{

}

void SceneManager::Exit()
{

}