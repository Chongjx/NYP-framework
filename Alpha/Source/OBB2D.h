/******************************************************************************/
/*!
\file	OBB2D.h
\author Jun Xiang
\brief
Create a 2D hitbox
*/
/******************************************************************************/
#ifndef OBB2D_H
#define OBB2D_H

#include <string>
#include <vector>

#include "Vector2.h"
#include "MyMath.h"

using std::string;
using std::vector;
using namespace Math;

/******************************************************************************/
/*!
Class OBB2D:
\brief	To store hitbox midpoint, length, height and unit vectors
*/
/******************************************************************************/
class OBB2D
{
private:
	Vector2 m_v2MidPoint;

	float m_fLength;
	float m_fHeight;

	float m_fHalfLength;
	float m_fHalfHeight;

	Vector2 m_v2UnitVecX;
	Vector2 m_v2UnitVecY;

	string m_sName;
public:
	OBB2D(void);
	~OBB2D(void);

	void create2Dhitbox(Vector2 midPoint, float length, float height, const string name);
	void create2Dhitbox(Vector2 bottomRight, Vector2 topRight, Vector2 topLeft, Vector2 bottomLeft, const string name);

	void setMidPoint(Vector2 midPoint);
	void setLength(float length);
	void setHeight(float height);

	void setHalfLength(float halfLength);
	void setHalfHeight(float halfHeight);

	void setName(string name);

	Vector2 getMidPoint(void) const;
	float getLength(void) const;
	float getHeight(void) const;

	float getHalfLength(void) const;
	float getHalfHeight(void) const;

	string getName(void) const;

	friend void check2DCollision(OBB2D &user, vector<OBB2D> &target, bool &collide, string &boxName);
	friend void check2DCollision(OBB2D &user, OBB2D &target, bool &collide, string &boxName);
};

#endif