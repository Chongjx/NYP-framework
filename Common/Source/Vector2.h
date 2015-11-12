#ifndef VECTOR2_H
#define VECTOR2_H

#include "MyMath.h"
#include <iostream>

struct Vector2
{
	float x, y;
	bool IsEqual(float a, float b) const;

	Vector2(float a = 0, float b = 0); //default constructor
	Vector2(const Vector2 &rhs); //copy constructor
	~Vector2();

	void Set (float a, float b); //Set all data
	void SetZero(void);
	bool IsZero(void) const;

	Vector2 operator+(const Vector2& rhs) const; //Vector addition
	Vector2& operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& rhs) const; //Vector subtraction
	Vector2& operator-=(const Vector2& rhs);

	Vector2 operator-( void ) const; //Unary negation

	Vector2 operator*( float scalar ) const; //Scalar multiplication
	Vector2& operator*=(float scalar);

	bool operator==(const Vector2& rhs) const; //Equality check
	bool operator!= (const Vector2& rhs) const; //Inequality check

	Vector2& operator=(const Vector2& rhs); //Assignment operator

	float Length( void ) const; //Get magnitude
	float Dot( const Vector2& rhs ) const; //Dot product
	Vector2 Normalized( void ); //Return a copy of this vector, normalized

	friend std::ostream& operator<<( std::ostream& os, Vector2& rhs); //print to ostream

	friend Vector2 operator*( float scalar, const Vector2& rhs ); //what is this for?
};

#endif
