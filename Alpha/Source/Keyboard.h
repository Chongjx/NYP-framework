#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>
#include <vector>

using std::vector;

class Keyboard
{
public:
	static Keyboard& getInstance()
	{
		static Keyboard keyboard;
		return keyboard;
	}

	void Init(void);
	void Update(void);

	bool getKey(unsigned short key);

	vector<bool> keys;

private:
	Keyboard();
	~Keyboard();

	bool isKeyPressed(unsigned short key);
};

#endif