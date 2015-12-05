#include "SceneManager.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"

SceneManager::SceneManager()
{
	parameters.clear();
	lights.clear();
	lightEnabled = true;
	fontSize = specialFontSize = 1.f;
	debugInfo = false;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(const int width, const int height, ResourcePool* RM, InputManager* controls)
{
	this->sceneWidth = (float)width;
	this->sceneHeight = (float)height;
	this->resourceManager.Init(RM);
	this->inputManager = controls;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Math::InitRNG();
}

void SceneManager::Config(string directory)
{
}

void SceneManager::InitShader()
{
}

void SceneManager::BindShaders()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

void SceneManager::UpdateMouse()
{
	// updating mouse pos in the scene via a handler from the engine
	double x, y;
	x = Application::getMouse()->getCurrentPosX();
	y = Application::getMouse()->getCurrentPosY();

	int w = Application::getWindowWidth();
	int h = Application::getWindowHeight();

	mousePos.Set((float)x * sceneWidth / w, (h - (float)y) * sceneHeight / h);
}

void SceneManager::RenderLight()
{
}

void SceneManager::Update(double dt)
{
	fps = (float)(1.f / dt);

	this->inputManager->Update();

	if (inputManager->getKey("EnableDebugInfo"))
	{
		this->debugInfo = true;
	}

	else if (inputManager->getKey("DisableDebugInfo"))
	{
		this->debugInfo = false;
	}
}

void SceneManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneManager::PreRender(bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && lightEnabled)
	{
		glUniform1i(parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
	}
	else
	{
		glUniform1i(parameters[U_LIGHTENABLED], 0);
	}
}

void SceneManager::RenderPush(Mtx44 properties)
{
	modelStack.PushMatrix();
	modelStack.MultMatrix(properties);
}

void SceneManager::RenderPop()
{
	modelStack.PopMatrix();
}


/********************************************************************************
Render text onto the screen with reference position in the middle of the image
********************************************************************************/
void SceneManager::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh)
	{
		std::cout << "Unable to render text!" << std::endl;
		return;
	}

	glDisable(GL_DEPTH_TEST);
	glUniform1i(parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(parameters[U_LIGHTENABLED], 0);
	glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

}

/********************************************************************************
Render text onto the screen
********************************************************************************/
void SceneManager::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, float rotation)
{
	if (!mesh)
	{
		std::cout << "Unable to render text on screen!" << std::endl;
		return;
	}

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, double(sceneWidth), 0, double(sceneHeight), -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	if (rotation != 0.f)
	{
		modelStack.Rotate(rotation, 0, 0, 1);
	}
	modelStack.Scale(size, size, size);

	glUniform1i(parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(parameters[U_LIGHTENABLED], 0);
	glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
Render a mesh in 3D
********************************************************************************/
void SceneManager::Render3DMesh(Mesh* mesh, bool enableLight)
{
	if (!mesh)
	{
		std::cout << "Unable to render 3D mesh!" << std::endl;
		return;
	}

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && lightEnabled)
	{
		glUniform1i(parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}

	else
	{
		glUniform1i(parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID != NULL)
	{
		glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
}

/********************************************************************************
Render a mesh in 2D
********************************************************************************/
void SceneManager::Render2DMesh(Mesh *mesh, const bool enableLight, const Vector2 scale, const Vector2 pos, const float rotation)
{
	if (!mesh)
	{
		std::cout << "Unable to render 2D mesh!" << std::endl;
		return;
	}

	Mtx44 ortho;
	ortho.SetToOrtho(0, double(sceneWidth), 0, double(sceneHeight), -100, 100);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(pos.x, pos.y, 0);
	modelStack.Scale(scale.x, scale.y, 1);
	if (rotation != 0.f)
		modelStack.Rotate(rotation, 0, 0, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	if (mesh->textureID != NULL)
	{
		glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void SceneManager::Exit()
{
	projectileManager.CleanUp();

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
}