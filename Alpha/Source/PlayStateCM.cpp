#include "Application.h"

#include "MenuStateCM.h"
#include "PlayStateCM.h"
#include "PauseStateCM.h"

PlayStateCM PlayStateCM::playState;

PlayStateCM::PlayStateCM()
{
	this->update = true;
	this->draw = true;
	this->stateName = "Play";
}

PlayStateCM::~PlayStateCM()
{
}

void PlayStateCM::Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
{
	this->update = true;
	this->draw = true;
	this->stateName = "Play";

	this->scene = new SceneManagerCMPlay();

	scene->Init(width, height, RP, controls);

	Application::getMouse()->enableDeadZone();
}

void PlayStateCM::CleanUp()
{
	if (scene)
	{
		scene->Exit();
		delete scene;
		scene = NULL;
	}
}

void PlayStateCM::Config()
{
}

void PlayStateCM::Pause()
{
	this->update = false;
	this->draw = false;

	Application::getMouse()->disableDeadZone();
}

void PlayStateCM::Resume()
{
	this->scene->BindShaders();
	this->update = true;
	this->draw = true;

	Application::getMouse()->enableDeadZone();
}

void PlayStateCM::HandleEvents(GameStateManager* gameStateManager)
{
	if (scene->inputManager->getKey("Pause"))
	{
		gameStateManager->PushState(PauseStateCM::Instance());
		this->draw = true;
		this->update = true;
		gameStateManager->SetOverrideRender(true);
	}
}

void PlayStateCM::HandleEvents(GameStateManager* gameStateManager, const unsigned char key, const bool status)
{
}

void PlayStateCM::HandleEvents(GameStateManager* gameStateManager, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right)
{
}

void PlayStateCM::HandleEvents(GameStateManager* gameStateManager, const double yaw, const double pitch)
{
}

void PlayStateCM::Update(GameStateManager* gameStateManager)
{
}

void PlayStateCM::Update(GameStateManager* gsm, const double dt)
{
	if (update)
	{
		scene->Update(dt);
	}
}

void PlayStateCM::Draw(GameStateManager* gameStateManager)
{
	if (draw)
	{
		scene->Render();
	}
}