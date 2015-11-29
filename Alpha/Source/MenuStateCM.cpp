#include "Application.h"

#include "MenuStateCM.h"
#include "PlayStateCM.h"

MenuStateCM MenuStateCM::menuState;

MenuStateCM::MenuStateCM()
{
	this->update = true;
	this->draw = true;
	this->stateName = "Menu";
}

MenuStateCM::~MenuStateCM()
{
}

void MenuStateCM::Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
{
	this->update = true;
	this->draw = true;
	this->stateName = "Menu";

	this->scene = new SceneManagerCMMenu();

	scene->Init(width, height, RP, controls);
}

void MenuStateCM::CleanUp()
{
	if (scene)
	{
		scene->Exit();
		delete scene;
		scene = NULL;
	}
}

void MenuStateCM::Config()
{
}

void MenuStateCM::Pause()
{
	this->update = false;
	this->draw = false;
}

void MenuStateCM::Resume()
{
	this->scene->BindShaders();
	this->update = true;
	this->draw = true;
}

void MenuStateCM::HandleEvents(GameStateManager* gameStateManager)
{
	for (unsigned i = 0; i < scene->interactiveButtons.size(); ++i)
	{
		if (scene->interactiveButtons[i].getStatus() == Button2D::BUTTON_RELEASED)
		{
			if (scene->interactiveButtons[i].getName() == "Play")
			{
				gameStateManager->PushState(PlayStateCM::Instance());
			}

			else if (scene->interactiveButtons[i].getName() == "Instruction")
			{
			}

			else if (scene->interactiveButtons[i].getName() == "Quit")
			{
				gameStateManager->Quit();
			}

			break;
		}
	}
}

void MenuStateCM::HandleEvents(GameStateManager* gameStateManager, const unsigned char key, const bool status)
{
}

void MenuStateCM::HandleEvents(GameStateManager* gameStateManager, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right)
{
}

void MenuStateCM::HandleEvents(GameStateManager* gameStateManager, const double yaw, const double pitch)
{
}

void MenuStateCM::Update(GameStateManager* gameStateManager)
{
}

void MenuStateCM::Update(GameStateManager* gsm, const double dt)
{
	if (update)
	{
		scene->Update(dt);
	}
}

void MenuStateCM::Draw(GameStateManager* gameStateManager)
{
	if (draw)
	{
		scene->Render();
	}
}