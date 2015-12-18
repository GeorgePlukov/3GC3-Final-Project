#ifndef __STRUCTS_H__	//guard against cyclic dependancy
#define __STRUCTS_H__

typedef struct {
	float x, y, z;
} Vector3D;

typedef struct {
	float x, y, z, w;
} Vector4D;

typedef struct {
	float col [4];
} Color;

typedef struct{
	float arr [4];
} Param;


#endif