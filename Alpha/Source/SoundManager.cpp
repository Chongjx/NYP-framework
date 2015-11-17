#include "SoundManager.h"


SoundManager::SoundManager() :
			engine(NULL),
			Sound(NULL)
{
}

SoundManager::~SoundManager()
{
	if (Sound)
	{
		delete Sound;
		Sound = NULL;
	}
	if (engine)
	{
		delete engine;
		engine = NULL;
	}
}

void SoundManager::Init()
{
	engine = createIrrKlangDevice();
	if (!engine)
	{
		//Error Feedback
		std::cout << ("Could not startup engine\n");	
	}
}

void SoundManager::PlaySound(string directory)
{
	Sound = engine->play2D(directory.c_str());
}

