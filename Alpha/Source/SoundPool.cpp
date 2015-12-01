#include "SoundPool.h"

SoundPool::SoundPool() :
		engine(NULL),
		Sound(NULL)
{
}

SoundPool::~SoundPool()
{
	soundContainer.clear();

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

void SoundPool::Init()
{
	engine = createIrrKlangDevice();
	if (!engine)
	{
		//Error Feedback
		std::cout << ("Could not startup engine\n");
	}
}

void SoundPool::processSound(string config)
{
	Branch soundBranch = TextTree::FileToRead(config);

	for (vector<Branch>::iterator branch = soundBranch.childBranches.begin(); branch != soundBranch.childBranches.end(); ++branch)
	{
		SOUND tempSound;

		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;

			if (attriName == "Directory")
			{
				tempSound.soundDirectory = tempAttri.value;
			}

			tempSound.name = branch->branchName;
			this->addSound(tempSound.name, tempSound);
		}
	}
}

bool SoundPool::addSound(string soundName, SOUND sound)
{
	map<string, SOUND>::iterator it = soundContainer.find(soundName);

	if (it != soundContainer.end())
	{
		return false;
	}
	else
	{
		soundContainer.insert(std::pair<string, SOUND>(soundName, sound));

		return true;
	}
}

void SoundPool::setListenerPos(Vector3 position,Vector3 target)
{
	engine->setListenerPosition(vec3df(position.x, position.y, position.z), vec3df(target.x,target.y,target.z));
}
void SoundPool::setEngineVolume(float value)
{
	//Maximum volume 
	if (value > 100)
	{
		value = 100;
	}
	//Minimum volume
	else if (value < 0)
	{
		value = 0;
	}

	value *= 0.01f;	//Converting to 0 - 1 value

	engine->setSoundVolume(value);
}

void SoundPool::retrieveSound2D(string soundName, bool loop)
{
	map<string, SOUND>::iterator it = soundContainer.find(soundName);

	if (it != soundContainer.end())
	{
		engine->play2D(it->second.soundDirectory.c_str(), loop);
	}
	else
	{
		std::cout << "Sound file not found!" << std::endl;
	}
}
void SoundPool::retrieveSound3D(string soundName, Vector3 position, bool loop)
{
	map<string, SOUND>::iterator it = soundContainer.find(soundName);

	if (it != soundContainer.end())
	{
		engine->play3D(it->second.soundDirectory.c_str(), vec3df(position.x, position.y, position.z), loop);
	}
	else
	{
		std::cout << "Sound file not found!" << std::endl;
	}
}

void SoundPool::IncreaseEngineVolume()
{
	float volume = engine->getSoundVolume();
	if (volume >= 1.0f)
	{
		//Do nothing if volume is already at maximum
		return;
	}
	else
	{
		volume += 0.1f;	//Increasing current volume by 10
		if (volume > 1.0f)
		{
			volume = 1.0f;
		}
		engine->setSoundVolume(volume);
	}
}
void SoundPool::DecreaseEngineVolume()
{
	float volume = engine->getSoundVolume();
	if (volume <= 0.f)
	{
		//Do nothing if volume is already at minimum
		return;
	}
	else
	{
		volume -= 0.1f;	//Decreasing current volume by 10
		if (volume <= 0.f)
		{
			volume = 0.f;
		}
		engine->setSoundVolume(volume);
	}
}

void SoundPool::cleanUp()
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

	soundContainer.clear();
}