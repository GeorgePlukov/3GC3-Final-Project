#ifndef __NODETRANSFORM_H__	//guard against cyclic dependancy
#define __NODETRANSFORM_H__

#include "node.h"
#include "../PMath/PPoint.h"

enum transformType
{
	Translate,
	Rotate,
	Scale
};

class NodeTransform:public Node
{
public:
	NodeTransform(transformType whatType, PPoint3f point3f);
	NodeTransform(transformType whatType, PPoint4f point4f);

	transformType transformationType;
	PPoint3f amount3;
	PPoint4f amount4;

	virtual void nodeSpecificCodeDown();
};

#endif