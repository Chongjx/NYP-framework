#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>
#include <string>

using std::vector;
using std::string;

struct KEYS
{
	string name;
	int value;
	bool pressed;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Init();
	void Update();
	bool getKey(string keyName);

private:
	vector<KEYS> inputKeys;
};

#endif