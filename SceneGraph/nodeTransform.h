#ifndef __NODETRANSFORM_H__	//guard against cyclic dependancy
#define __NODETRANSFORM_H__

#include "node.h"
#include "../PMath/PPoint.h"

enum TransformType
{
	Translate,
	Rotate,
	Scale
};

class NodeTransform:public Node
{
public:
	NodeTransform(TransformType whatType, PPoint3f point3f);
	NodeTransform(TransformType whatType, PPoint4f point4f);
	NodeTransform(TransformType whatType);

	TransformType transformationType;
	PPoint3f amount3;
	PPoint4f amount4;

	virtual void nodeSpecificCodeDown();
};

#endif