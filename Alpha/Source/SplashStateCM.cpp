#include "Application.h"

#include "SplashStateCM.h"
#include "MenuStateCM.h"

SplashStateCM SplashStateCM::splashState;

SplashStateCM::SplashStateCM()
{
	this->update = true;
	this->draw = true;
	this->stateName = "Splash";
}

SplashStateCM::~SplashStateCM()
{
}

void SplashStateCM::Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
{
	this->update = true;
	this->draw = true;
	this->stateName = "Splash";

	this->scene = new SceneManagerCMSplash();

	scene->Init(width, height, RP, controls);
}

void SplashStateCM::CleanUp()
{
	if (scene)
	{
		scene->Exit();
		delete scene;
		scene = NULL;
	}
}

void SplashStateCM::Config()
{
}

void SplashStateCM::Pause()
{
	this->update = false;
	this->draw = false;
}

void SplashStateCM::Resume()
{
	this->scene->BindShaders();
	this->update = true;
	this->draw = true;
}

void SplashStateCM::HandleEvents(GameStateManager* gameStateManager)
{
	// if the splash screen completes
	if (scene->getExit())
	{
		gameStateManager->PushState(MenuStateCM::Instance());
	}
}

void SplashStateCM::HandleEvents(GameStateManager* gameStateManager, const unsigned char key, const bool status)
{
}

void SplashStateCM::HandleEvents(GameStateManager* gameStateManager, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right)
{
}

void SplashStateCM::HandleEvents(GameStateManager* gameStateManager, const double yaw, const double pitch)
{
}

void SplashStateCM::Update(GameStateManager* gameStateManager)
{
}

void SplashStateCM::Update(GameStateManager* gsm, const double dt)
{
	if (update)
	{
		scene->Update(dt);
	}
}

void SplashStateCM::Draw(GameStateManager* gameStateManager)
{
	if (draw)
	{
		scene->Render();
	}
}