#ifndef OPTION_STATE_H
#define OPTION_STATE_H

#include "GameState.h"

class OptionState// : public GameState
{
private:
	static OptionState optionState;

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

	static OptionState* Instance()
	{
		return &optionState;
	}

protected:
	OptionState();
	virtual ~OptionState();
};

#endif