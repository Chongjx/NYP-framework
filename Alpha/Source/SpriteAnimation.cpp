#include "SpriteAnimation.h"
#include "GL\glew.h"
#include "Vertex.h"

SpriteAnimation::SpriteAnimation():
	Mesh(""), m_row(0), m_col(0), m_currentFrame(0)
{
	animations.resize(0);
}

SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col) : Mesh(meshName), m_row(row), m_col(col), m_currentFrame(0)
{
	animations.resize(0);
}

SpriteAnimation::~SpriteAnimation()
{
	for (vector<Animation*>::iterator it = animations.begin(); it != animations.end(); ++it)
	{
		Animation* ani = *it;
		if (ani != NULL)
		{
			delete ani;
			ani = NULL;
		}
	}
}

SpriteAnimation& SpriteAnimation::operator=(SpriteAnimation &copy)
{
	this->textureID = copy.textureID;
	this->vertexBuffer = copy.vertexBuffer;
	this->indexBuffer = copy.indexBuffer;
	this->indexSize = copy.indexSize;
	this->material = copy.material;
	this->m_row = copy.m_row;
	this->m_col = copy.m_col;

	this->animations.resize(copy.animations.size());

	for (unsigned numAnimations = 0; numAnimations < animations.size(); ++numAnimations)
	{
		this->animations[numAnimations] = new Animation();
		*(this->animations[numAnimations]) = *(copy.animations[numAnimations]);
	}

	return *this;
}

void SpriteAnimation::Update(double dt)
{
	static float animationSpeed = 10;
	if (this->animations[currentAni])
	{
		if (!this->animations[currentAni]->paused)
		{
			this->animations[currentAni]->currentTime += animationSpeed * (float)dt;

			static int numFrame = 0;

			if ((this->animations[currentAni]->endFrame - this->animations[currentAni]->startFrame + 1) < 1)
			{
				numFrame = 1;
			}

			else
			{
				numFrame = this->animations[currentAni]->endFrame - this->animations[currentAni]->startFrame + 1;
			}

			float frameTime = this->animations[currentAni]->animTime / numFrame;

			if ((this->animations[currentAni]->startFrame + this->animations[currentAni]->currentTime / frameTime) < this->animations[currentAni]->endFrame)
			{
				this->m_currentFrame = (int)(this->animations[currentAni]->startFrame + this->animations[currentAni]->currentTime / frameTime);
			}

			else
			{
				this->m_currentFrame = this->animations[currentAni]->endFrame;
			}

			if(this->animations[currentAni]->currentTime > this->animations[currentAni]->animTime)
			{
				if (this->animations[currentAni]->playLooped)
				{
					this->animations[currentAni]->currentTime = 0;
					this->m_currentFrame = this->animations[currentAni]->startFrame;
				}
			}
		}
	}
}

void SpriteAnimation::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if(mode == DRAW_LINES)
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
	else if(mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
	else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}