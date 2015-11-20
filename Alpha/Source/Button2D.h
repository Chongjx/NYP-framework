#ifndef BUTTON_2D_H
#define BUTTON_2D_H

#include "StaticGameObject.h"
#include "GameObject2D.h"

class Button2D : public StaticGameObject, public GameObject2D
{
public:
	enum BUTTON_TYPE
	{
		TEXT_BUTTON,
		IMAGE_BUTTON,
		MAX_TYPE,
	};

	enum BUTTON_STATUS
	{
		BUTTON_PRESSED,
		BUTTON_RELEASED,
		BUTTON_HOVER,
		BUTTON_IDLE,
		MAX_STATUS,
	};

	Button2D();
	~Button2D();

	void Init(string name, string text, Mesh* mesh, Vector2 pos, Vector2 scale, float rotation, Color textColor, BUTTON_TYPE type, BUTTON_STATUS status = BUTTON_IDLE);

	void Update(bool pressed, Vector2 mouse);
	void Update(bool pressed, double mouseX, double mouseY);

	void setName(string name);
	void setText(string text);
	void setScale(Vector2 scale);
	void setRotation(float rotation);
	void setColor(Color col);
	void setType(BUTTON_TYPE type);
	void setStatus(BUTTON_STATUS status);

	string getName(void) const;
	string getText(void) const;
	Vector2 getScale(void) const;
	float getRotation(void) const;
	Color getColor(void) const;
	BUTTON_TYPE getType(void) const;
	BUTTON_STATUS getPrevStatus(void) const;
	BUTTON_STATUS getStatus(void) const;
private:
	string name;
	string text;
	Vector2 scale;
	float rotation;
	Color textCol;
	BUTTON_TYPE type;
	BUTTON_STATUS prevStatus;
	BUTTON_STATUS status;
};

#endif