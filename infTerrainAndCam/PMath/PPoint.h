#ifndef __PPOINT_H__
#define __PPOINT_H__

#include <stdio.h>

class PPoint3f 
{
public:
	//Public Variables
	float x,y,z;

	//Constructors
	PPoint3f();
	PPoint3f(float, float, float);

	void giveValue();
};

class PPoint4f
{
public:
	float w,x,y,z;

	//Constructors
	PPoint4f();
	PPoint4f(float, float, float, float);

	void giveValue();
};

#endif
