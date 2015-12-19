#ifndef __NODEMODEL_H__	
#define __NODEMODEL_H__

#include "node.h"
#include "../includes.h"

enum ModelType
{
	Helicopter,
	Ground,
	Wall,
	Target
};

class NodeModel:public Node
{
public:
	NodeModel(ModelType whatType);
	NodeModel(ModelType whatType, Material *m);
	Material *m;
	ModelType modelType;

	virtual void nodeSpecificCodeDown();

private:
	void drawGround();
};

#endif