#ifndef FOG_H
#define FOG_H

#include "Vector3.h"

struct Fog
{
	enum FOG_TYPE
	{
		FOG_LINEAR = 0,
		FOG_EXPONENT,
		FOG_EXPONENTSQ,
	};

	FOG_TYPE type;	// Type of fog
	Vector3 color;	// Fog color
	float start;	// For linear fog
	float end;		// For linear fog
	float density;	// For exponential fog
	bool enabled;	// Toggle fog

	Fog()
	{
		type = FOG_LINEAR;
		color.Set(0.1f, 0.1f, 0.1f);
		start = 200;
		end = 2000;
		density = 0.005f;
		enabled = true;
	}
};

#endif