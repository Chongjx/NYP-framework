#include "Button2D.h"
#include "Application.h"

Button2D::Button2D() :
name(""),
text(""),
type(TEXT_BUTTON),
status(BUTTON_IDLE)
{
}

Button2D::~Button2D()
{
}

void Button2D::Init(string name, string text, Mesh* mesh, Vector2 pos, Vector2 scale, float rotation, Color col, BUTTON_TYPE type, BUTTON_STATUS status)
{
	this->name = name;
	this->text = text;
	this->mesh = mesh;
	this->position = Vector3(pos.x, pos.y, 0);
	this->scale = scale;
	this->rotation = rotation;
	this->targetRotation = this->rotation;
	this->textCol = col;
	this->type = type;
	this->prevStatus = this->status = status;

	this->rotate = false;
}

void Button2D::Update(bool pressed, Vector2 mouse)
{
	prevStatus = status;

	// update Button2D status based on mouse position
	if (mouse.x < this->position.x + this->scale.x && mouse.x > this->position.x)
	{
		if (mouse.y < this->position.y + this->scale.y && mouse.y > this->position.y)
		{
			if (prevStatus == BUTTON_PRESSED && !pressed)
			{
				this->status = BUTTON_RELEASED;
			}

			else if (pressed)
			{
				this->status = BUTTON_PRESSED;
			}

			else
			{
				this->status = BUTTON_HOVER;
			}
		}

		else
		{
			this->status = BUTTON_IDLE;
		}
	}

	else
	{
		this->status = BUTTON_IDLE;
	}
}

void Button2D::Update(bool pressed, double mouseX, double mouseY)
{
	prevStatus = status;

	// update Button2D status based on mouse position
	if (mouseX < this->position.x + this->scale.x && mouseX > this->position.x)
	{
		if (mouseY < this->position.y + this->scale.y && mouseY > this->position.y)
		{
			if (prevStatus == BUTTON_PRESSED && !pressed)
			{
				this->status = BUTTON_RELEASED;
			}

			else if (pressed)
			{
				this->status = BUTTON_PRESSED;
			}

			else
			{
				this->status = BUTTON_HOVER;
			}
		}

		else
		{
			this->status = BUTTON_IDLE;
		}
	}

	else
	{
		this->status = BUTTON_IDLE;
	}
}

void Button2D::setName(string name)
{
	this->name = name;
}

void Button2D::setText(string text)
{
	this->text = text;
}

void Button2D::setScale(Vector2 scale)
{
	this->scale = scale;
}

void Button2D::setRotation(float rotation)
{
	this->rotation = rotation;

	if (Math::FAbs(targetRotation - this->rotation) < 10)
	{
		this->rotation = this->targetRotation;
		rotate = false;
	}
}

void Button2D::setTargetRotation(float rotation)
{
	this->targetRotation = rotation;

	if (this->rotation != targetRotation)
	{
		rotate = true;
	}
}

void Button2D::setColor(Color col)
{
	this->textCol = col;
}

void Button2D::setType(BUTTON_TYPE type)
{
	this->type = type;
}

void Button2D::setStatus(BUTTON_STATUS status)
{
	this->status = status;
}

string Button2D::getName(void) const
{
	return this->name;
}

string Button2D::getText(void) const
{
	return this->text;
}

Vector2 Button2D::getScale(void) const
{
	return this->scale;
}

float Button2D::getRotation(void) const
{
	return this->rotation;
}

float Button2D::getTargetRotation(void) const
{
	return this->targetRotation;
}

Color Button2D::getColor(void) const
{
	return this->textCol;
}

Button2D::BUTTON_TYPE Button2D::getType(void) const
{
	return this->type;
}

Button2D::BUTTON_STATUS Button2D::getPrevStatus(void) const
{
	return this->prevStatus;
}

Button2D::BUTTON_STATUS Button2D::getStatus(void) const
{
	return this->status;
}

bool Button2D::getRotate(void) const
{
	return this->rotate;
}