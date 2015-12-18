#ifndef __NODEMODEL_H__	
#define __NODEMODEL_H__

#include "node.h"
#include "../includes.h"

enum ModelType
{
	Sphere,
	Cube,
	Teapot,
	Custom
};

class NodeModel:public Node
{
public:
	NodeModel(ModelType whatType, Material *m);	//constructor
	Material *m;
	ModelType modelType;

	virtual void nodeSpecificCodeDown();
};

#endif