/******************************************************************************/
/*!
\file	OBB3D.h
\author Jun Xiang
\brief
Create a 3D hitbox
*/
/******************************************************************************/
#ifndef OBB3D_H
#define OBB3D_H

#include <string>
#include <vector>

#include "Vector3.h"
#include "MyMath.h"
#include "Mtx44.h"

using std::string;
using std::vector;
using namespace Math;

/******************************************************************************/
/*!
Class OBB3D:
\brief	To store hitbox midpoint, length, height, depth and unit vectors
*/
/******************************************************************************/
class OBB3D
{
private:
	Vector3 m_v3MidPoint;

	float m_fLength;
	float m_fHeight;
	float m_fDepth;

	float m_fHalfLength;
	float m_fHalfHeight;
	float m_fHalfDepth;

	Vector3 m_v3UnitVecX;
	Vector3 m_v3UnitVecY;
	Vector3 m_v3UnitVecZ;

	string m_sName;
	bool m_bCollide;
public:
	OBB3D(void);
	OBB3D(Vector3 midPoint, float length, float height, float depth, const string name);
	~OBB3D(void);

	void create3Dhitbox(Vector3 midPoint, float length, float height, float depth, const string name);
	void create3Dhitbox(Vector3 frontBottomRight, Vector3 frontTopRight, Vector3 frontTopLeft, Vector3 frontBottomLeft, Vector3 backBottomRight, Vector3 backTopRight, Vector3 backTopLeft, Vector3 backBottomLeft, const string name);

	void setMidPoint(Vector3 newMidPoint);
	void setLength(float length);
	void setHeight(float height);
	void setDepth(float depth);

	void setHalfLength(float halfLength);
	void setHalfHeight(float halfHeight);
	void setHalfDepth(float halfDepth);

	void setUnitVecX(Vector3 uniVecX);
	void setUnitVecY(Vector3 uniVecY);
	void setUnitVecZ(Vector3 uniVecZ);

	void setName(string name);
	void setCollide(bool collide);

	Vector3 getMidPoint(void) const;
	float getLength(void) const;
	float getHeight(void) const;
	float getDepth(void) const;

	float getHalfLength(void) const;
	float getHalfHeight(void) const;
	float getHalfDepth(void) const;

	Vector3 getUnitVecX(void) const;
	Vector3 getUnitVecY(void) const;
	Vector3 getUnitVecZ(void) const;

	string getName(void) const;
	bool getCollide(void) const;

	friend bool check3DCollision(OBB3D &user, vector<OBB3D> &target, string &boxName);
	friend bool check3DCollision(OBB3D &user, OBB3D &target, string &boxName);

	OBB3D &operator= (OBB3D &input);
};

#endif