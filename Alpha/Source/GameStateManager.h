#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <vector>
#include <string>

#include "SceneManagerSelection.h"
#include "SceneManagerGameplay.h"
#include "SceneManagerInfo.h"
#include "ResourcePool.h"

using std::vector;
using std::string;

class GameState;

class GameStateManager
{
private:
	vector<GameState*> statesStack;

	string title;
	int windowWidth;
	int windowHeight;

	bool running;
	bool fullscreen;
	bool overrideUpdate;
	bool overrideRender;

	bool run;
public:
	GameStateManager();
	~GameStateManager();

	void Init();
	void Init(string title, int width, int height, bool run = true, bool fullScreen = false);
	void InitResources(string config);
	void InitControls(string config);
	void Config();

	void CleanUp();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState(GameState* state);
	void PopToState(GameState* toState);
	void PopToState(string stateName);

	GameState* GetPrevious();
	GameState* GetPrevious(unsigned index);
	
	bool validCheck(void);

	void HandleEvents(void);
	void HandleEvents(const unsigned char key, const bool status = true);
	void HandleEvents(const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right);
	void HandleEvents(const double yaw, const double pitch);
	void Update(const double m_dElapsedTime);
	void Draw();

	bool Running(void);
	void Quit(void);

	void SetOverrideUpdate(bool update);
	void SetOverrideRender(bool render);

	ResourcePool* resourcePool;
	InputManager* controls;
};

#endif