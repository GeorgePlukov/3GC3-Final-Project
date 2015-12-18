#ifndef MATERIAL_D
#define MATERIAL_D
#include "includes.h"


class Material {
public:
	Param diff, spec, amb;
	float reflect;
	// Constructor
	Material(Param , Param, Param, float);
	void enable();
};

#endif

