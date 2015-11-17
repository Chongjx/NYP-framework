#include "InputManager.h"
#include "Application.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Init()
{

}

void InputManager::Update()
{
	// updating keyboard intput via a handler from the engine
	for (unsigned i = 0; i < inputKeys.size(); ++i)
	{
		inputKeys[i].pressed = Application::getKeyboard()->getKey(inputKeys[i].value);
	}
}

bool InputManager::getKey(string keyName)
{
	for (unsigned i = 0; i < inputKeys.size(); ++i)
	{
		if (keyName == inputKeys[i].name)
		{
			return inputKeys[i].pressed;
		}
	}

	std::cout << "No such key! Check your naming!" << std::endl;
	return false;
}