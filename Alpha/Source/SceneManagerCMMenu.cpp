#include "SceneManagerCMMenu.h"

SceneManagerCMMenu::SceneManagerCMMenu()
{
}

SceneManagerCMMenu::~SceneManagerCMMenu()
{
}

void SceneManagerCMMenu::Init(const int width, const int height, ResourcePool *RM, InputManager* controls)
{
	SceneManagerSelection::Init(width, height, RM, controls);

	Config();

	this->InitShader();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	mouseMesh = resourceManager.retrieveMesh("CURSOR");

	fireball = (SpriteAnimation*)resourceManager.retrieveMesh("FIREBALL_SPRITE");
}

void SceneManagerCMMenu::Config()
{
	SceneManagerSelection::Config("Config\\GameStateConfig\\MenuConfig.txt");
}

void SceneManagerCMMenu::Update(double dt)
{
	SceneManagerSelection::Update(dt);

	if (inputManager->getKey("Select"))
	{
		fireball->Update(dt);
	}

	UpdateMouse();
	UpdateSelection();
}

void SceneManagerCMMenu::Render()
{
	SceneManagerSelection::Render();

	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Set up the view
	viewStack.LoadIdentity();
	viewStack.LookAt(fpCamera.getPosition().x, fpCamera.getPosition().y, fpCamera.getPosition().z,
		fpCamera.getTarget().x, fpCamera.getTarget().y, fpCamera.getTarget().z,
		fpCamera.getUp().x, fpCamera.getUp().y, fpCamera.getUp().z);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderLight();
	RenderBG();
	RenderStaticObject();
	RenderMobileObject();
	RenderSelection();
}

void SceneManagerCMMenu::Exit()
{
	SceneManagerSelection::Exit();
}

void SceneManagerCMMenu::BindShaders()
{
	SceneManagerSelection::BindShaders();
}

// Other specific init, update and render classes
void SceneManagerCMMenu::InitShader()
{
	SHADER thisShader = resourceManager.retrieveShader("Comg");
	programID = LoadShaders(thisShader.vertexShaderDirectory.c_str(), thisShader.fragmentShaderDirectory.c_str());

	this->BindShaders();
	parameters.resize(U_TOTAL);
	lights.resize(1);

	// Get a handle for our uniform
	parameters[U_MVP] = glGetUniformLocation(programID, "MVP");
	//parameters[U_MODEL] = glGetUniformLocation(programID, "M");
	//parameters[U_VIEW] = glGetUniformLocation(programID, "V");
	parameters[U_MODELVIEW] = glGetUniformLocation(programID, "MV");
	parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(programID, "MV_inverse_transpose");
	parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(programID, "material.kAmbient");
	parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(programID, "material.kDiffuse");
	parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(programID, "material.kSpecular");
	parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(programID, "material.kShininess");
	parameters[U_LIGHTENABLED] = glGetUniformLocation(programID, "lightEnabled");
	parameters[U_NUMLIGHTS] = glGetUniformLocation(programID, "numLights");
	parameters[U_LIGHT0_TYPE] = glGetUniformLocation(programID, "lights[0].type");
	parameters[U_LIGHT0_POSITION] = glGetUniformLocation(programID, "lights[0].position_cameraspace");
	parameters[U_LIGHT0_COLOR] = glGetUniformLocation(programID, "lights[0].color");
	parameters[U_LIGHT0_POWER] = glGetUniformLocation(programID, "lights[0].power");
	parameters[U_LIGHT0_KC] = glGetUniformLocation(programID, "lights[0].kC");
	parameters[U_LIGHT0_KL] = glGetUniformLocation(programID, "lights[0].kL");
	parameters[U_LIGHT0_KQ] = glGetUniformLocation(programID, "lights[0].kQ");
	parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(programID, "lights[0].spotDirection");
	parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(programID, "lights[0].cosCutoff");
	parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(programID, "lights[0].cosInner");
	parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(programID, "lights[0].exponent");
	// Get a handle for our "colorTexture" uniform
	parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(programID, "colorTextureEnabled");
	parameters[U_COLOR_TEXTURE] = glGetUniformLocation(programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	parameters[U_TEXT_ENABLED] = glGetUniformLocation(programID, "textEnabled");
	parameters[U_TEXT_COLOR] = glGetUniformLocation(programID, "textColor");

	// Use our shader
	glUseProgram(programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 0, 10);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 0.f, 1.f);

	glUniform1i(parameters[U_NUMLIGHTS], 1);
	glUniform1i(parameters[U_TEXT_ENABLED], 0);

	glUniform1i(parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(parameters[U_LIGHT0_EXPONENT], lights[0].exponent);
}

void SceneManagerCMMenu::RenderLight()
{

}

void SceneManagerCMMenu::RenderBG()
{

}

void SceneManagerCMMenu::RenderStaticObject()
{
}

void SceneManagerCMMenu::RenderMobileObject()
{
}

void SceneManagerCMMenu::RenderSelection()
{
	SceneManagerSelection::RenderSelection();

	// Render mouse
	Render2DMesh(mouseMesh, false, Vector2(50, 50), Vector2(mousePos.x, mousePos.y), 90.f);

	if (inputManager->getKey("Select"))
	{
		Render2DMesh(fireball, false, Vector2(100, 100), Vector2(mousePos.x + 50, mousePos.y));
	}
}

void SceneManagerCMMenu::UpdateMouse()
{
	SceneManagerSelection::UpdateMouse();
}

void SceneManagerCMMenu::UpdateSelection()
{
	SceneManagerSelection::UpdateSelection();

	for (unsigned i = 0; i < (unsigned)interactiveButtons.size(); ++i)
	{
		if (interactiveButtons[i].getStatus() != interactiveButtons[i].getPrevStatus())
		{
			if (interactiveButtons[i].getStatus() == Button2D::BUTTON_PRESSED)
			{
				interactiveButtons[i].setColor(resourceManager.retrieveColor("Red"));
			}

			else if (interactiveButtons[i].getStatus() == Button2D::BUTTON_IDLE)
			{
				interactiveButtons[i].setColor(resourceManager.retrieveColor("White"));
			}

			else if (interactiveButtons[i].getStatus() == Button2D::BUTTON_HOVER)
			{
				interactiveButtons[i].setColor(resourceManager.retrieveColor("Orange"));
			}
		}
	}
}