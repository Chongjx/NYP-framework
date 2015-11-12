#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include <vector>

using std::vector;

struct Animation
{
	Animation()
	{
		this->ID = -1;
		this->startFrame = 0;
		this->endFrame = 0;
		this->playLooped = false;
		this->paused = true;
		this->animTime = 0.f;
		this->currentTime = 0.f;
	}

	Animation& operator=(Animation &copy)
	{
		this->ID = copy.ID;
		this->startFrame = copy.startFrame;
		this->endFrame = copy.endFrame;
		this->playLooped = copy.playLooped;
		this->paused = copy.paused;
		this->animTime = copy.animTime;
		this->currentTime = copy.currentTime;

		return *this;
	}

	void Set(int ID, int startFrame, int endFrame, bool playLooped, bool startPaused, float animTime, float currentTime = 0.f)
	{
		this->ID = ID;
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->playLooped = playLooped;
		this->paused = startPaused;
		this->animTime = animTime;
		this->currentTime = currentTime;
	}

	int ID;
	int startFrame;
	int endFrame;
	bool playLooped;
	bool paused;
	float animTime;
	float currentTime;
};

class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation();
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();

	SpriteAnimation& operator=(SpriteAnimation &copy);

	void Update(double dt);
	virtual void Render();

	int m_row;
	int m_col;

	int m_currentFrame;
	int currentAni;
	vector<Animation*> animations;
};

#endif