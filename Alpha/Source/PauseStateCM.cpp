#include "Application.h"

#include "PauseStateCM.h"
#include "PlayStateCM.h"

PauseStateCM PauseStateCM::pauseState;

PauseStateCM::PauseStateCM()
{
	this->update = true;
	this->draw = true;
	this->stateName = "Pause";
}

PauseStateCM::~PauseStateCM()
{
}

void PauseStateCM::Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
{
	this->update = true;
	this->draw = true;
	this->stateName = "Pause";

	this->scene = new SceneManagerCMPause();

	scene->Init(width, height, RP, controls);

	Application::getMouse()->disableDeadZone();
}

void PauseStateCM::CleanUp()
{
	if (scene)
	{
		scene->Exit();
		delete scene;
		scene = NULL;
	}
}

void PauseStateCM::Config()
{
}

void PauseStateCM::Pause()
{
	this->update = false;
	this->draw = false;
}

void PauseStateCM::Resume()
{
	this->scene->BindShaders();
	this->update = true;
	this->draw = true;
}

void PauseStateCM::HandleEvents(GameStateManager* gameStateManager)
{
	for (unsigned i = 0; i < scene->interactiveButtons.size(); ++i)
	{
		if (scene->interactiveButtons[i].getStatus() == Button2D::BUTTON_RELEASED)
		{
			if (scene->interactiveButtons[i].getName() == "Resume")
			{
				scene->interactiveButtons[i].setStatus(Button2D::BUTTON_IDLE);
				gameStateManager->PopState(this);
				
			}

			else if (scene->interactiveButtons[i].getName() == "Menu")
			{
				scene->interactiveButtons[i].setStatus(Button2D::BUTTON_IDLE);
				gameStateManager->PopToState("Menu");
			}

			gameStateManager->SetOverrideRender(false);

			break;
		}
	}

	/*if (scene->inputManager->getKey("Select"))
	{
		gameStateManager->PopToState("Menu");
		gameStateManager->SetOverrideRender(false);
	}

	else if (scene->inputManager->getKey("RSelect"))
	{
		gameStateManager->PopState(this);
		gameStateManager->SetOverrideRender(false);
	}*/
}

void PauseStateCM::HandleEvents(GameStateManager* gameStateManager, const unsigned char key, const bool status)
{
}

void PauseStateCM::HandleEvents(GameStateManager* gameStateManager, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right)
{
}

void PauseStateCM::HandleEvents(GameStateManager* gameStateManager, const double yaw, const double pitch)
{
}

void PauseStateCM::Update(GameStateManager* gameStateManager)
{
}

void PauseStateCM::Update(GameStateManager* gsm, const double dt)
{
	if (update)
	{
		scene->Update(dt);
	}
}

void PauseStateCM::Draw(GameStateManager* gameStateManager)
{
	if (draw)
	{
		scene->Render();
	}
}