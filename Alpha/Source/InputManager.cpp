#include "InputManager.h"
#include "Application.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Init(string config)
{
	inputBranch = TextTree::FileToRead(config);

	Config();
}

void InputManager::Config()
{
	for (vector<Branch>::iterator branch = inputBranch.childBranches.begin(); branch != inputBranch.childBranches.end(); ++branch)
	{
		KEYS tempKey;

		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;
			
			tempKey.name = branch->branchName;

			if (attriName == "Key")
			{
				tempKey.value = stol(attriValue, NULL, 16);
			}
		}

		inputKeys.push_back(tempKey);
	}
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