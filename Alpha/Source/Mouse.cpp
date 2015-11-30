#include "Application.h"
#include "Mouse.h"


Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Config(void)
{
	for (vector<Branch>::iterator branch = mouseBranch.childBranches.begin(); branch != mouseBranch.childBranches.end(); ++branch)
	{
		if (branch->branchName == "SetUp")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "currentPos")
				{
					string xCoord;
					string yCoord;
					int lastContinue = 0;
					for (unsigned j = 0; j < attriValue.size() && attriValue[j] != ','; ++j)
					{
						xCoord += attriValue[j];
						lastContinue = j + 2;
					}

					for (unsigned j = lastContinue; j < attriValue.size(); ++j)
					{
						yCoord += attriValue[j];
					}

					this->currentPosX = stoi(xCoord);
					this->currentPosY = stoi(yCoord);
				}

				else if (attriName == "sensitivity")
				{
					this->sensitivity = stof(attriValue);
				}

				else if (attriName == "deadzone")
				{
					stringToVector(attriValue, deadZoneDimension);
				}
			}
		}
	}

	this->diffPos.SetZero();
	this->lastPos.SetZero();
	this->mouseYaw = 0;
	this->mousePitch = 0;
	deadzone = false;

	for (int i = LEFT_BUTTON; i < MAX_BUTTON; ++i)
	{
		mouseButtonStatus[i] = false;
	}
}

void Mouse::Init(string config)
{
	mouseBranch = TextTree::FileToRead(config);

	Config();
}

// update mouse pos and button status
void Mouse::Update()
{
	for (int i = LEFT_BUTTON; i < MAX_BUTTON; ++i)
	{
		mouseButtonStatus[i] = false;
	}

	glfwGetCursorPos(m_window, &currentPosX, &currentPosY);

	diffPos.x = (float)currentPosX - lastPos.x;
	diffPos.y = (float)currentPosY - lastPos.y;

	mouseYaw = (float)(diffPos.x * 0.0174555555555556f * sensitivity); // 3.142f / 180.0f );
	mousePitch = (float)(diffPos.y * 0.0174555555555556f * sensitivity); // 3.142f / 180.0f );

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	if (deadzone)
	{
		if ((currentPosX < deadZoneDimension.x) || (currentPosX > Application::getWindowWidth() - deadZoneDimension.x))
		{
			currentPosX = Application::getWindowWidth() >> 1;
			glfwSetCursorPos(m_window, currentPosX, currentPosY);
		}

		if ((currentPosY < deadZoneDimension.y) || (currentPosY > Application::getWindowHeight() - deadZoneDimension.y))
		{
			currentPosY = Application::getWindowHeight() >> 1;
			glfwSetCursorPos(m_window, currentPosX, currentPosY);
		}
	}

	lastPos.Set((float)currentPosX, (float)currentPosY);

	for (int i = LEFT_BUTTON; i < MAX_BUTTON; ++i)
	{
		if (glfwGetMouseButton(m_window, i) == GLFW_PRESS)
		{
			mouseButtonStatus[i] = true;
		}
	}
}

void Mouse::setMouseYaw(double value)
{
	this->mouseYaw = value;
}

void Mouse::setMousePitch(double value)
{
	this->mousePitch = value;
}

void Mouse::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

void Mouse::enableDeadZone()
{
	this->deadzone = true;
}

void Mouse::disableDeadZone()
{
	this->deadzone = false;
}

void Mouse::setMousePos(const double xCoord, const double yCoord)
{
	this->currentPosX = xCoord;
	this->currentPosY = xCoord;
}

double Mouse::getCurrentPosX(void)
{
	return this->currentPosX;
}

double Mouse::getCurrentPosY(void)
{
	return this->currentPosY;
}

Vector2 Mouse::getLastPos(void)
{
	return this->lastPos;
}

Vector2 Mouse::getDiffPos(void)
{
	return this->diffPos;
}

double Mouse::getMouseYaw(void) const
{
	return this->mouseYaw;
}

double Mouse::getMousePitch(void) const
{
	return this->mousePitch;
}

float Mouse::getSensitivity(void) const
{
	return this->sensitivity;
}