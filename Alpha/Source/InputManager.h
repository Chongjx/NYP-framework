#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>
#include <string>
#include <TextBranch.h>

using std::vector;
using std::string;

struct KEYS
{
	string name = "";
	int value = 0;
	bool pressed = false;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Init(string config);
	void Config();
	void Update();
	bool getKey(string keyName);

private:
	Branch inputBranch;
	vector<KEYS> inputKeys;
};

#endif