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

void SoundPool::retrieveSound(string soundName)
{
	map<string, SOUND>::iterator it = soundContainer.find(soundName);

	if (it != soundContainer.end())
	{
		engine->play2D(it->second.soundDirectory.c_str(), false);
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
}