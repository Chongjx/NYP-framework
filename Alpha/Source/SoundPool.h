#ifndef SOUND_POOL_H
#define SOUND_POOL_H

#include <map>
#include <string>
#include "irrKlang.h"
#include "TextTree.h"

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
	void retrieveSound(string soundName);
	void Init();
	void processSound(string config);

	SoundPool();
	~SoundPool();

private:
	map<string, SOUND> soundContainer;	//Contains sound files directory
	bool addSound(string soundName, SOUND sound);
	
	ISoundEngine* engine;	//Sound engine
	ISound* Sound;	//Sound pointer to be played

};

#endif