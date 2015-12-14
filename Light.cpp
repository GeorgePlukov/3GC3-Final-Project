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
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "structs.h"
// float light_pos0[] = { 0.0f, 50.0f, 0.0f, 1.0f};
// float amb0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
// float diff0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
// float spec0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
// glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
// 	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
//
// float light_pos1[] = { 100.0f, 50.0f, 100.0f, 1.0f};
// float amb1[4] = {0.1f, 0.2f, 0.1f, 1.0f};
// float diff1[4] = {0.5f, 0.5f, 0.5f, 1.0f};
// float spec1[4] = {0.5f, 0.5f, 0.5f, 1.0f};
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







