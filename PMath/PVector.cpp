#include "PVector.h"

/************************************************/
/*			    	PVector3f	    			*/
/************************************************/
PVector3f::PVector3f() 
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	magnitude = 0.0f;
}

PVector3f::PVector3f(float ax, float ay, float az)
{
	x = ax;
	y = ay;
	z = az;
	magnitude = calcMagnitude();
}

PVector3f::PVector3f(PPoint3f p1, PPoint3f p2)
{
	x = p2.x - p1.x; 
	y = p2.y - p1.y;
	z = p2.z - p1.z;
	magnitude = calcMagnitude();
}


float PVector3f::calcMagnitude()
{
	return sqrt((x*x)+(y*y)+(z*z));
}

void PVector3f::normalize()
{
	x /= magnitude; 
	y /= magnitude; 
	z /= magnitude;
	magnitude = calcMagnitude();
}

void PVector3f::giveValue()
{
	printf("(%f,%f,%f) --> %f\n", x,y,z, magnitude);
}

/*Math Operator Overloads!*/
PVector3f PVector3f::operator +(const PVector3f& other)
{
	PVector3f sum(x + other.x, y + other.y, z + other.z);
	return sum;
}

PVector3f PVector3f::operator -(const PVector3f& other)
{
	PVector3f difference(x - other.x, y - other.y, z - other.z);
	return difference;
}

PVector3f PVector3f::operator -()
{
	PVector3f urinary(-x, -y, -z);
	return urinary;
}

PVector3f PVector3f::operator *(const PVector3f& other)
{
	PVector3f crossed (y * other.z - z * other.x, 
				 	 z * other.x - x * other.z,
				 	 x * other.y - y * other.x);
	return crossed;
}

PVector3f PVector3f::operator *(const float factor)
{
	PVector3f product(x * factor, y * factor, z * factor);
	return product;
}


/************************************************/
/*			    	PVector4f	    			*/
/************************************************/
PVector4f::PVector4f() 
{
	w = 0.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	magnitude = 0.0f;
}

PVector4f::PVector4f(float aw, float ax, float ay, float az)
{
	w = aw;
	x = ax;
	y = ay;
	z = az;
	magnitude = calcMagnitude();
}

PVector4f::PVector4f(PPoint4f p1, PPoint4f p2)
{
	x = p2.w - p1.w;
	x = p2.x - p1.x; 
	y = p2.y - p1.y;
	z = p2.z - p1.z;
	magnitude = calcMagnitude();
}

float PVector4f::calcMagnitude()
{
	return sqrt((w*w)+(x*x)+(y*y)+(z*z));
}

void PVector4f::normalize()
{
	w /= magnitude;
	x /= magnitude; 
	y /= magnitude; 
	z /= magnitude;
	magnitude = calcMagnitude();
}

void PVector4f::giveValue()
{
	printf("(%f,%f,%f,%f) --> %f\n", w,x,y,z, magnitude);
}

/*Math Operator Overloads!*/
PVector4f PVector4f::operator +(const PVector4f& other)
{
	PVector4f sum(w + other.w, x + other.x, y + other.y, z + other.z);
	return sum;
}

PVector4f PVector4f::operator -(const PVector4f& other)
{
	PVector4f difference(w - other.w, x - other.x, y - other.y, z - other.z);
	return difference;
}

PVector4f PVector4f::operator -()
{
	PVector4f urinary(-w, -x, -y, -z);
	return urinary;
}

PVector4f PVector4f::operator *(const float factor)
{
	PVector4f product(w * factor, x * factor, y * factor, z * factor);
	return product;
}


