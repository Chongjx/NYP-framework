#include "SceneManagerCMPlay.h"

SceneManagerCMPlay::SceneManagerCMPlay() : 
sceneGraph(NULL)
{
}

SceneManagerCMPlay::~SceneManagerCMPlay()
{
	if (sceneGraph)
	{
		sceneGraph->CleanUp();
		delete sceneGraph;
		sceneGraph = NULL;
	}
}

void SceneManagerCMPlay::Init(const int width, const int height, ResourcePool *RM, InputManager* controls)
{
	SceneManagerGameplay::Init(width, height, RM, controls);

	this->InitShader();

	//tpCamera.Init(Vector3(0, 0, -10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	tpCamera.Init(Vector3(0, 0, -10), Vector3(0, 0, 0), Vector3(0, 1, 0), false, false);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	InitSceneGraph();

	lightEnabled = true;

	SpatialPartitionManager SPM;

	//SPM.Init(Vector3(-2000, 0, -2000), Vector3(2000, 2000, 2000), Vector3(20, 10, 20), true, resourceManager.retrieveMesh("DEBUG_CUBE"));
}

void SceneManagerCMPlay::Config()
{

}

void SceneManagerCMPlay::Update(double dt)
{
	SceneManagerGameplay::Update(dt);

	projectileManager.Update(dt);

	/*Sound testing related keys*/
	if (inputManager->getKey("TEST_SOUND"))
	{
		resourceManager.setListenerPosition(tpCamera.getPosition(), tpCamera.getTarget());
		static int distance = 2;
		//distance++;
		//resourceManager.retrieveSoundas2D("MenuFeedback");
		resourceManager.retrieveSoundas3D("MenuFeedback", tpCamera.getPosition() + (float)distance);
	}

	if (inputManager->getKey("VOLUME_UP"))
	{
		resourceManager.IncreaseSoundEngineVolume();
	}
	if (inputManager->getKey("VOLUME_DOWN"))
	{
		resourceManager.DecreaseSoundEngineVolume();
	}

	tpCamera.UpdatePosition(sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition(), Vector3(0,0,0));
	//tpCamera.Update(dt);

	if (inputManager->getKey("ToggleWireFrame"))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else if (inputManager->getKey("ToggleFill"))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (inputManager->getKey("Fire"))
	{
		projectileManager.FetchProjectile(sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition(), 
			(tpCamera.getTarget() - tpCamera.getPosition()).Normalized(),
			20.f, resourceManager.retrieveMesh("MAGE_OBJ"));
	}

	if (inputManager->getKey("LockPitch"))
	{
		tpCamera.TogglePitchLock();
	}
	if (inputManager->getKey("LockYaw"))
	{
		tpCamera.ToggleYawLock();
	}

	if (inputManager->getKey("Up"))
	{
		sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x + 10.f * dt,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z));
	}

	if (inputManager->getKey("Down"))
	{
		sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x - 10.f * dt,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z));
	}

	if (inputManager->getKey("Left"))
	{
		sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z - 10.f * dt));
	}

	if (inputManager->getKey("Right"))
	{
		sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z + 10.f * dt));
	}
}

void SceneManagerCMPlay::Render()
{
	SceneManagerGameplay::Render();

	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Set up the view
	viewStack.LoadIdentity();
	viewStack.LookAt(tpCamera.getPosition().x, tpCamera.getPosition().y, tpCamera.getPosition().z,
		tpCamera.getTarget().x, tpCamera.getTarget().y, tpCamera.getTarget().z,
		tpCamera.getUp().x, tpCamera.getUp().y, tpCamera.getUp().z);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderLight();
	RenderBG();
	RenderStaticObject();
	RenderMobileObject();
}

void SceneManagerCMPlay::Exit()
{
	if (sceneGraph)
	{
		sceneGraph->CleanUp();
		sceneGraph = NULL;
	}

	SceneManagerGameplay::Exit();
}

void SceneManagerCMPlay::BindShaders()
{
	SceneManagerGameplay::BindShaders();
}

// Other specific init, update and render classes
void SceneManagerCMPlay::InitShader()
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
	lights[0].position.Set(0, 10, 10);
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

void SceneManagerCMPlay::RenderLight()
{

}

void SceneManagerCMPlay::RenderBG()
{

}

void SceneManagerCMPlay::RenderStaticObject()
{
	Mesh* drawMesh = resourceManager.retrieveMesh("SKYPLANE");

	modelStack.PushMatrix();
	modelStack.Translate(0, 2000, 0);
	Render3DMesh(drawMesh, false);
	modelStack.PopMatrix();

	drawMesh = resourceManager.retrieveMesh("FLOOR");

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(100.0f, 100.0f, 100.0f);
	Render3DMesh(drawMesh, false);
	modelStack.PopMatrix();
}

void SceneManagerCMPlay::RenderMobileObject()
{
	FSMApplication();
	sceneGraph->Draw(this);
	projectileManager.Draw(this);
}

void SceneManagerCMPlay::InitSceneGraph()
{
	this->sceneGraph = new SceneNode();

	//**********//
	//Warrior	//
	//**********//
	GameObject3D* newModel = new GameObject3D;
	SceneNode* newNode = new SceneNode;
	Mesh* drawMesh = resourceManager.retrieveMesh("WARRIOR_OBJ");

	newModel->setMesh(drawMesh);
	newModel->setName("WARRIOR");
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("WARRIOR_SWORD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("WARRIOR_SWORD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("WARRIOR", newNode);

	drawMesh = resourceManager.retrieveMesh("WARRIOR_SHIELD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("WARRIOR_SHIELD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("WARRIOR", newNode);


	//**********//
	//Healer	//
	//**********//
	drawMesh = resourceManager.retrieveMesh("HEALER_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("HEALER");
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("HEALER_ROD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("HEALER_ROD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("HEALER", newNode);


	//**********//
	//Mage		//
	//**********//
	drawMesh = resourceManager.retrieveMesh("MAGE_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("MAGE");
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("MAGE_STAFF_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("MAGE_STAFF");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("MAGE", newNode);

	//**********//
	//Boss		//
	//**********//
	drawMesh = resourceManager.retrieveMesh("BOSS_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("BOSS");
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("BOSS_ARM_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("BOSS_R_ARM");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("BOSS", newNode);

	drawMesh = resourceManager.retrieveMesh("BOSS_ARM_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("BOSS_L_ARM");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	sceneGraph->AddChildToChildNode("BOSS", newNode);
}

void SceneManagerCMPlay::FSMApplication()
{
	Vector3 newPosition;
	//sceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(newPosition);
	//sceneGraph->GetChildNode("Warrior")->GetGameObject()->setRotation(90, 0, 1, 0);
	sceneGraph->GetChildNode("WARRIOR_SWORD")->GetGameObject()->setPosition(Vector3(0, 0, -5));
	sceneGraph->GetChildNode("WARRIOR_SHIELD")->GetGameObject()->setPosition(Vector3(0, 0, 5));


	newPosition.Set(-40, 0, -20);
	sceneGraph->GetChildNode("HEALER")->GetGameObject()->setPosition(newPosition);
	sceneGraph->GetChildNode("HEALER_ROD")->GetGameObject()->setPosition(Vector3(0, 0, -5));


	newPosition.Set(-40, 0, 20);
	sceneGraph->GetChildNode("MAGE")->GetGameObject()->setPosition(newPosition);
	sceneGraph->GetChildNode("MAGE_STAFF")->GetGameObject()->setPosition(Vector3(0, 0, -5));


	newPosition.Set(-60, 0, 0);
	sceneGraph->GetChildNode("BOSS")->GetGameObject()->setPosition(newPosition);
	sceneGraph->GetChildNode("BOSS_L_ARM")->GetGameObject()->setPosition(Vector3(0, 0, -5));
	sceneGraph->GetChildNode("BOSS_R_ARM")->GetGameObject()->setPosition(Vector3(0, 0, 5));
}

void SceneManagerCMPlay::UpdateMouse()
{
	SceneManagerGameplay::UpateMouse();
}