#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager() :
	title(""),
	windowWidth(1920),
	windowHeight(1080),
	running(true),
	fullscreen(false),
	resourcePool(NULL)
{
}

GameStateManager::~GameStateManager()
{
	// Cleanup all the states
	while (!statesStack.empty())
	{
		statesStack.back()->CleanUp();
		statesStack.pop_back();
	}

	if (resourcePool)
	{
		resourcePool->CleanUp();
		delete resourcePool;
		resourcePool = NULL;
	}
}

void GameStateManager::Init()
{
	this->title = "";
	this->windowWidth = 1920;
	this->windowHeight = 1080;
	this->running = true;
	this->fullscreen = false;
	resourcePool = new ResourcePool();
}

void GameStateManager::Init(string title, int width, int height, bool run, bool fullScreen)
{
	this->title = title;
	this->windowWidth = width;
	this->windowHeight = height;
	this->running = run;
	this->fullscreen = fullScreen;
	this->resourcePool = new ResourcePool();
}

void GameStateManager::CleanUp()
{
	// Cleanup all the states
	while (!statesStack.empty())
	{
		statesStack.back()->CleanUp();
		statesStack.pop_back();
	}

	// Cleanup all the resources used
	if (resourcePool)
	{
		resourcePool->CleanUp();
		delete resourcePool;
		resourcePool = NULL;
	}
}

bool GameStateManager::validCheck(void)
{
	if (statesStack.size() > 0)
	{
		return true;
	}

	return false;
}

void GameStateManager::ChangeState(GameState* state)
{
	// cleanup the current state
	if (!statesStack.empty()) {
		statesStack.back()->CleanUp();
		statesStack.pop_back();
	}

	// store and init the new state
	statesStack.push_back(state);
	statesStack.back()->Init(windowWidth, windowHeight);
}

void GameStateManager::PushState(GameState* state)
{
	// pause current state
	if (!statesStack.empty()) {
		statesStack.back()->Pause();
	}

	// store and init the new state
	statesStack.push_back(state);
	statesStack.back()->Init(windowWidth, windowHeight);
}

void GameStateManager::PopState(GameState* state)
{
	// cleanup the current state
	if (!statesStack.empty()) {
		statesStack.back()->CleanUp();
		statesStack.pop_back();
	}

	// resume previous state
	if (!statesStack.empty()) {
		statesStack.back()->Resume();
	}
}

void GameStateManager::HandleEvents(void)
{
	// let the state handle events
	statesStack.back()->HandleEvents(this);
}

void GameStateManager::HandleEvents(const unsigned char key, const bool status)
{
	// let the state handle events
	statesStack.back()->HandleEvents(this, key, status);
}

void GameStateManager::HandleEvents(const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
	// let the state handle events
	statesStack.back()->HandleEvents(this, mouse_x, mouse_y, button_Left, button_Middle, button_Right);
}

void GameStateManager::HandleEvents(const double yaw, const double pitch)
{
	// let the state handle events
	statesStack.back()->HandleEvents(this, yaw, pitch);
}

void GameStateManager::Update(const double m_dElapsedTime)
{
	// let the state update the gameStateManager
	statesStack.back()->Update(this, m_dElapsedTime);
}

void GameStateManager::Draw()
{
	// let the state draw the screen
	statesStack.back()->Draw(this);
}

bool GameStateManager::Running(void)
{
	return running;
}

void GameStateManager::Quit(void)
{
	running = false;
}