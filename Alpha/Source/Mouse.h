#ifndef MOUSE_H
#define MOUSE_H

#include "GLFW\glfw3.h"
#include <string>
#include "TextTree.h"
#include "Vector2.h"

using std::string;

enum MOUSE_KEY
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON,
	MAX_BUTTON,
};

class Mouse
{
private:
	double currentPosX;
	double currentPosY;
	Vector2 lastPos, diffPos;
	double mouseYaw, mousePitch;
	float sensitivity;
	bool deadzone;

	Vector2 deadZoneDimension;

	void Config(void);
public:
	Mouse();
	~Mouse();

	Branch mouseBranch;

	void Init(string config);
	void Update();

	void setMouseYaw(double value);
	void setMousePitch(double value);
	void setSensitivity(float sensitivity);
	void enableDeadZone();
	void disableDeadZone();

	void setMousePos(const double xCoord, const double yCoord);
	double getCurrentPosX(void);
	double getCurrentPosY(void);
	Vector2 getLastPos(void);
	Vector2 getDiffPos(void);

	double getMouseYaw(void) const;
	double getMousePitch(void) const;
	float getSensitivity(void) const;
	GLFWwindow* m_window;
	bool mouseButtonStatus[MAX_BUTTON];
};

#endif