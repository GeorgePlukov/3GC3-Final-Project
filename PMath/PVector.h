#ifndef __PVector_H__
#define __PVector_H__

#include <cstdio>
#include <cmath>
#include "PPoint.h"

class PVector3f 
{
public:
	//Public Variables
	float x,y,z;
	float magnitude;

	//Constructors
	PVector3f();
	PVector3f(float, float, float);
	PVector3f(PPoint3f, PPoint3f);

	//Public Functions
	float calcMagnitude();
	void normalize();
	void giveValue();

	//Math Methods!
	PVector3f operator +(const PVector3f&);
	PVector3f operator -(const PVector3f&);
	PVector3f operator -();
	PVector3f operator *(const PVector3f&);
	PVector3f operator *(const float);
	
};

class PVector4f
{
public:
	//public variables
	float w,x,y,z;
	float magnitude;

	//Constructors
	PVector4f();
	PVector4f(float, float, float, float);
	PVector4f(PPoint4f, PPoint4f);

	//Public Functions
	float calcMagnitude();
	void normalize();
	void giveValue();

	//Math Methods
	PVector4f operator +(const PVector4f&);
	PVector4f operator -(const PVector4f&);
	PVector4f operator -();
	PVector4f operator *(const float);

};


#endif