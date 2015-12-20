#ifndef __NODEMODEL_H__	
#define __NODEMODEL_H__

#include "node.h"
#include "../includes.h"

enum ModelType
{
	Helicopter,
	Ground,
	Building,
	Target
};

class NodeModel:public Node
{
public:
	NodeModel(ModelType whatType, GLuint t);
	NodeModel(ModelType whatType, Material *m, GLuint t);
	ModelType modelType;
	Material *m;
	GLuint tex;

	virtual void nodeSpecificCodeDown();

private:
	void drawGround();
	void georgeSolidCube();

};

#endif