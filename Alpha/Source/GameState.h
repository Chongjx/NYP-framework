#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameStateManager.h"

class GameState
{
public:
	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls) = 0;
	virtual void CleanUp() = 0;

	virtual void Config() = 0;

	virtual void HandleEvents(GameStateManager* gameStateManager) = 0;
	virtual void HandleEvents(GameStateManager* gameStateManager, const unsigned char key, const bool status = true) = 0;
	virtual void HandleEvents(GameStateManager* gameStateManager, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right) = 0;
	virtual void HandleEvents(GameStateManager* gameStateManager, const double yaw, const double pitch) = 0;
	
	virtual void Update(GameStateManager* gameStateManager) = 0;
	virtual void Update(GameStateManager* gameStateManager, const double dt) = 0;
	
	virtual void Draw(GameStateManager* gameStateManager) = 0;

	virtual void Pause()
	{
		this->update = false;
		this->draw = false;
	}

	virtual void Resume()
	{
		this->update = true;
		this->draw = true;
	}

	virtual void ChangeState(GameStateManager* gameStateManager, GameState* state)
	{
		gameStateManager->ChangeState(state);
	}

	virtual void PushState(GameStateManager* gameStateManager, GameState* state)
	{
		gameStateManager->PushState(state);
	}

	virtual void PopState(GameStateManager* gameStateManager, GameState* state)
	{
		gameStateManager->PopState(state);
	}

	virtual void SetName(string stateName)
	{
		this->stateName = stateName;
	}

	virtual string GetName(void)
	{
		return stateName;
	}

protected:
	GameState() {}
	virtual ~GameState() {}

	string stateName;
	bool update;
	bool draw;
};

#endif