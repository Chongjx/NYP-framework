#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>
#include <vector>

using std::vector;

class Keyboard
{
public:
	Keyboard(void);
	~Keyboard(void);

	void Init(void);
	void Update(void);

	bool getKey(unsigned short key);

	vector<bool> keys;

private:
	bool isKeyPressed(unsigned short key);
};

#endif