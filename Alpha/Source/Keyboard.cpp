#include "Keyboard.h"

Keyboard::Keyboard()
{
	keys.resize(VK_OEM_CLEAR);
}

Keyboard::~Keyboard()
{
}

void Keyboard::Init(void)
{
	for (unsigned i = 0; i < VK_OEM_CLEAR; ++i)
	{
		keys[i] = false;
	}
}

void Keyboard::Update(void)
{
	for (unsigned short i = 0; i < VK_OEM_CLEAR; ++i)
	{
		keys[i] = false;

		if (isKeyPressed(i))
		{
			keys[i] = true;
		}
	}
}

bool Keyboard::getKey(unsigned short key)
{
	return keys[key];
}

bool Keyboard::isKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}