#include "Application.h"

#include "MenuStateCM.h"
#include "PlayStateCM.h"

PlayStateCM PlayStateCM::playState;

PlayStateCM::PlayStateCM()
{
	this->update = true;
	this->draw = true;
}

PlayStateCM::~PlayStateCM()
{
}

void PlayStateCM::Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
{
	this->update = true;
	this->draw = true;

	this->scene = new SceneManagerCMPlay();

	scene->Init(width, height, RP, controls);
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
}

void PlayStateCM::Resume()
{
	this->update = true;
	this->draw = true;
}

void PlayStateCM::HandleEvents(GameStateManager* gameStateManager)
{
	if (scene->inputManager->getKey("RSelect"))
	{
		gameStateManager->PushState(MenuStateCM::Instance());
	}
	/*this->scene->interactiveButtons[i].Update(this->scene->inputManager->getKey("Select"), Application::getMouse()->getCurrentPosX(), Application::getMouse()->getCurrentPosY());*/
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