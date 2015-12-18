#ifndef __NODEMODEL_H__	
#define __NODEMODEL_H__

#include "node.h"


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
	NodeModel(ModelType whatType);	//constructor
	ModelType modelType;

	virtual void nodeSpecificCodeDown();
};

#endif