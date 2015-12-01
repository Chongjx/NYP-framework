#ifndef SOUND_POOL_H
#define SOUND_POOL_H

#include <map>
#include <string>
#include "irrKlang.h"
#include "TextTree.h"
#include "Vector3.h"

using namespace irrklang;

using std::string;
using std::map;

struct SOUND
{
	string name = "";
	string soundDirectory = "";
};

class SoundPool
{
public:
	void Init();	//Initialize sound engine
	void processSound(string config);	//Process sound from txt files

	void IncreaseEngineVolume();	//Increase current volume by 10
	void DecreaseEngineVolume();	//Decrease current volume by 10

	void setEngineVolume(float value);	//Set engine volume
	void setListenerPos(Vector3 position, Vector3 target);	//Let engine know where listener position is at

	void retrieveSound2D(string soundName,const bool loop = false);	//Plays retrieved sound in 2D
	void retrieveSound3D(string soundName,Vector3 position,const bool loop = false);	//Plays retrieved sound in 3D

	void cleanUp();	//Clean up

	SoundPool();
	~SoundPool();

private:
	map<string, SOUND> soundContainer;	//Contains sound files directory
	bool addSound(string soundName, SOUND sound);
	
	ISoundEngine* engine;	//Sound engine
	ISound* Sound;	//Sound pointer to be played

};

#endif