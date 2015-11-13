#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"

class PlayState// : public GameState
{
private:
	static PlayState playState;

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

	static PlayState* Instance()
	{
		return &playState;
	}

protected:
	PlayState();
	virtual ~PlayState();
};

#endif