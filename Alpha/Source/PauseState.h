#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameState.h"

class PauseState// : public GameState
{
private:
	static PauseState pauseState;

public:
	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Config();

	void Pause();
	void Resume();

	void HandleEvents(GameStateManager* theGSM);
	void HandleEvents(GameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(GameStateManager* theGSM, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right);
	void HandleEvents(GameStateManager* theGSM, const double yaw, const double pitch);
	void Update(GameStateManager* theGSM);
	void Update(GameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(GameStateManager* theGSM);

	static PauseState* Instance()
	{
		return &pauseState;
	}

protected:
	PauseState();
	virtual ~PauseState();
};

#endif