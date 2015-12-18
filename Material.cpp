#include "Material.h"
#include "includes.h"



Material::Material(Param diff, Param spec, Param amb, float r) {
	this->diff = diff;
	this->spec = spec;
	this->amb = amb;
	this->reflect = r;
}
void Material::enable() {
	/* MATERIALS */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->diff.arr);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->amb.arr);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->spec.arr);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->reflect);
}