#include "PPoint.h"

//Constructors
PPoint3f::PPoint3f() 
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

PPoint3f::PPoint3f(float ax, float ay, float az)
{
	x = ax;
	y = ay;
	z = az;
}

void PPoint3f::giveValue()
{
	printf("(%f,%f,%f)\n", x,y,z);
}

PPoint4f::PPoint4f() 
{
	w = 0.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

PPoint4f::PPoint4f(float aw, float ax, float ay, float az)
{
	w = aw;
	x = ax;
	y = ay;
	z = az;
}

void PPoint4f::giveValue()
{
	printf("(%f,%f,%f,%f)\n", w,x,y,z);
}