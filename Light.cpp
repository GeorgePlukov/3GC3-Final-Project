/*
 * File:   Light.h
 * Author: kurtbradd
 *
 */


#include "Light.h"
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "structs.h"
// Constructor
Light::Light(int glLight, Param posIn, Param diffIn , Param specIn, Param ambIn) {
	pos = posIn;
	dif = diffIn;
	spec = specIn;
	amb = ambIn;
	lightNum = glLight;
}

// Operators
void Light::enable() {
	// Enable the light source and set its parameters

	switch (lightNum) {
	case 1:
		glEnable(GL_LIGHT0);
		break;
	case 2:
		glEnable(GL_LIGHT1);
	case 3:
		glEnable(GL_LIGHT2);
		break;

	}
	glLightfv(lightNum, GL_POSITION, pos.arr);
	glLightfv(lightNum, GL_AMBIENT, amb.arr);
	glLightfv(lightNum, GL_DIFFUSE, dif.arr);
	glLightfv(lightNum, GL_SPECULAR, spec.arr);
}

void Light::redrawLight() {
	glLightfv(lightNum, GL_POSITION, pos.arr);
}

void Light::increaseX(int val) {
	pos.arr[0] += val;
	redrawLight();
}
void Light::decreaseX(int val) {
	pos.arr[0] -= val;
	redrawLight();

}
void Light::increaseY(int val) {
	pos.arr[1] += val;
	redrawLight();

}
void Light::decreaseY(int val) {
	pos.arr[1] -= val;
	redrawLight();

}
void Light::increaseZ(int val) {
	pos.arr[2] += val;
	redrawLight();

}
void Light::decreaseZ(int val) {
	pos.arr[2] -= val;
	redrawLight();

}







