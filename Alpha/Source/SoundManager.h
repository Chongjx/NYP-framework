#pragma once
#include "irrKlang.h"
#include <iostream>
#include <string>

using std::string;
using namespace irrklang;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Init();	//Create sound engine
	
	void PlaySound(string directory);	//Plays sound based on directory

private:
	ISoundEngine* engine;	//Sound engine
	ISound* Sound;	//Sound pointer to be played
};

