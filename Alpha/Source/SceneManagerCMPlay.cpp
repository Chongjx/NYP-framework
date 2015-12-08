#include "SceneManagerCMPlay.h"

SceneManagerCMPlay::SceneManagerCMPlay() :
sceneGraph(NULL),
staticSceneGraph(NULL),
dynamicSceneGraph(NULL)/*,
miniMap(NULL)*/
{
}

SceneManagerCMPlay::~SceneManagerCMPlay()
{
	SceneManagerCMPlay::Exit();
}

void SceneManagerCMPlay::Init(const int width, const int height, ResourcePool *RM, InputManager* controls)
{
	SceneManagerGameplay::Init(width, height, RM, controls);

	Config();

	this->InitShader();
	this->InitSceneGraph();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	textMesh = resourceManager.retrieveMesh("FONT");

	/*
	miniMap = new MiniMap();
	miniMap->Init();
	*/
}

void SceneManagerCMPlay::Config()
{
	SceneManagerGameplay::Config("Config\\GameStateConfig\\PlayConfig.txt");
}

void SceneManagerCMPlay::Update(double dt)
{
	SceneManagerGameplay::Update(dt);
	FSMApplication();

	//spatialPartitionManager->Update();
	spatialPartitionManager->removeNode(dynamicSceneGraph);
	spatialPartitionManager->addNode(dynamicSceneGraph, this->spatialPartitionManager->type);

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

	tpCamera.UpdatePosition(dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition(), Vector3(0, 0, 0));
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
		Vector3 characterPos = dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition();
		projectileManager.FetchProjectile(characterPos, (tpCamera.getTarget() - characterPos).Normalized(), 20.f, resourceManager.retrieveMesh("MAGE_OBJ"));
	}

	if (inputManager->getKey("LockPitch"))
	{
		tpCamera.TogglePitchLock();
	}
	if (inputManager->getKey("LockYaw"))
	{
		tpCamera.ToggleYawLock();
	}

	const float moveSpeed = 100.f;
	if (inputManager->getKey("Up"))
	{
		dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x - moveSpeed * (float)dt,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z));
	}

	if (inputManager->getKey("Down"))
	{
		dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x + moveSpeed * (float)dt,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z));
	}

	if (inputManager->getKey("Left"))
	{
		dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z + moveSpeed * (float)dt));
	}

	if (inputManager->getKey("Right"))
	{
		dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->setPosition(Vector3(
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().x,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().y,
			dynamicSceneGraph->GetChildNode("WARRIOR")->GetGameObject()->getPosition().z - moveSpeed * (float)dt));
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
	RenderGUI();
}

void SceneManagerCMPlay::Exit()
{
	if (sceneGraph)
	{
		sceneGraph->CleanUp();
		sceneGraph = NULL;
	}

	/*if (miniMap)
	{
		delete miniMap;
		miniMap = NULL;
	}*/

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
	staticSceneGraph->Draw(this);
	Mesh* drawMesh;

	drawMesh = resourceManager.retrieveMesh("WARRIOR_SWORD_OBJ");
	for (int i = 0; i < 4000; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 2000, 0);
		Render3DMesh(drawMesh, false);
		modelStack.PopMatrix();
	}

	drawMesh = resourceManager.retrieveMesh("SKYPLANE");
	modelStack.PushMatrix();
	modelStack.Translate(0, 2000, 0);
	Render3DMesh(drawMesh, false);
	modelStack.PopMatrix();

	drawMesh = resourceManager.retrieveMesh("FLOOR");

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	Render3DMesh(drawMesh, false);
	modelStack.PopMatrix();

	if (debugInfo)
	{
		for (int k = 0; k < (int)spatialPartitionManager->getNumPartition().z; ++k)
		{
			for (int j = 0; j < (int)spatialPartitionManager->getNumPartition().y; ++j)
			{
				for (int i = 0; i < (int)spatialPartitionManager->getNumPartition().x; ++i)
				{
					Partition* partition = spatialPartitionManager->getPartition(Vector3((float)i, (float)j, (float)k), false);
					if (partition->nodes.size() > 0)
					{
						std::cout << partition->nodes.size() << std::endl;
						modelStack.PushMatrix();
						modelStack.Translate(
							world3DStart.x + (i + 0.5f) * spatialPartitionManager->getParitionDimension().x,
							world3DStart.y + (j + 0.5f) * spatialPartitionManager->getParitionDimension().y,
							world3DStart.z + (k + 0.5f) * spatialPartitionManager->getParitionDimension().z);
						modelStack.Scale(spatialPartitionManager->getParitionDimension());
						Render3DMesh(partition->getMesh(), false);
						modelStack.PopMatrix();
					}
				}
			}
		}
	}
}

void SceneManagerCMPlay::RenderMobileObject()
{
	dynamicSceneGraph->Draw(this);
	projectileManager.Draw(this);
}

void SceneManagerCMPlay::RenderGUI()
{
	static Color textCol = resourceManager.retrieveColor("White");

	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(textMesh, ss.str(), textCol, 30, 0, sceneHeight- 30);
}

void SceneManagerCMPlay::InitSceneGraph()
{
	// root node
	this->sceneGraph = new SceneNode();

	// first child node of the scenegraph consists of static nodes / nodes that do not need constantly update
	this->staticSceneGraph = new SceneNode();
	// second child node of the scenegraph consists of dynamic / moving nodes / nodes that need to be updated with spatial partition for collision detection
	this->dynamicSceneGraph = new SceneNode();

	// add the 2 child to parent node first
	sceneGraph->AddChildNode(staticSceneGraph);
	sceneGraph->AddChildNode(dynamicSceneGraph);

	GameObject3D* newModel = new GameObject3D;
	SceneNode* newNode = new SceneNode;
	Mesh* drawMesh;

	// Add all mobile node into dynamicSceneGraph
	//**********//
	//Warrior	//
	//**********//
	drawMesh = resourceManager.retrieveMesh("WARRIOR_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("WARRIOR");
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("WARRIOR_SWORD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("WARRIOR_SWORD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("WARRIOR", newNode);

	drawMesh = resourceManager.retrieveMesh("WARRIOR_SHIELD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("WARRIOR_SHIELD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("WARRIOR", newNode);

	//**********//
	//Healer	//
	//**********//
	drawMesh = resourceManager.retrieveMesh("HEALER_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("HEALER");
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("HEALER_ROD_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("HEALER_ROD");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("HEALER", newNode);


	////**********//
	////Mage		//
	////**********//
	drawMesh = resourceManager.retrieveMesh("MAGE_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("MAGE");
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("MAGE_STAFF_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("MAGE_STAFF");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("MAGE", newNode);

	////**********//
	////Boss		//
	////**********//
	drawMesh = resourceManager.retrieveMesh("BOSS_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setMesh(drawMesh);
	newModel->setName("BOSS");
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildNode(newNode);

	drawMesh = resourceManager.retrieveMesh("BOSS_ARM_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("BOSS_R_ARM");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("BOSS", newNode);

	drawMesh = resourceManager.retrieveMesh("BOSS_ARM_OBJ");
	newModel = new GameObject3D;
	newNode = new SceneNode;
	newModel->setName("BOSS_L_ARM");
	newModel->setMesh(drawMesh);
	newNode->SetGameObject(newModel);
	dynamicSceneGraph->AddChildToChildNode("BOSS", newNode);

	// Rmb to init static nodes position first

	spatialPartitionManager->addNode(sceneGraph, spatialPartitionManager->type);
}

void SceneManagerCMPlay::FSMApplication()
{
	Vector3 newPosition;
	dynamicSceneGraph->GetChildNode("WARRIOR_SWORD")->GetGameObject()->setPosition(Vector3(0, 0, -5));
	dynamicSceneGraph->GetChildNode("WARRIOR_SHIELD")->GetGameObject()->setPosition(Vector3(0, 0, 5));


	newPosition.Set(-40, 0, -20);
	dynamicSceneGraph->GetChildNode("HEALER")->GetGameObject()->setPosition(newPosition);
	dynamicSceneGraph->GetChildNode("HEALER_ROD")->GetGameObject()->setPosition(Vector3(0, 0, -5));


	newPosition.Set(-40, 0, 20);
	dynamicSceneGraph->GetChildNode("MAGE")->GetGameObject()->setPosition(newPosition);
	dynamicSceneGraph->GetChildNode("MAGE_STAFF")->GetGameObject()->setPosition(Vector3(0, 0, -5));


	newPosition.Set(-60, 0, 0);
	dynamicSceneGraph->GetChildNode("BOSS")->GetGameObject()->setPosition(newPosition);
	dynamicSceneGraph->GetChildNode("BOSS_L_ARM")->GetGameObject()->setPosition(Vector3(0, 0, -5));
	dynamicSceneGraph->GetChildNode("BOSS_R_ARM")->GetGameObject()->setPosition(Vector3(0, 0, 5));
}

void SceneManagerCMPlay::UpdateMouse()
{
	SceneManagerGameplay::UpateMouse();
}