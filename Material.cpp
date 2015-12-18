#include "Material.h"
#include "includes.h"



Material::Material(Param diff, Param spec, Param amb, float reflect) {
	this.diff = diff;
	this.spec = spec;
	this.amb = amb;
	this.reflect = r;
}
void Material::enableMaterial() {
	/* MATERIALS */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this.dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this.amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this.spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this.reflect);
}