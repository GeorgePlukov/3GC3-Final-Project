#include "nodeTransform.h"
#include "../includes.h"
//for gltranslate and gl scale
NodeTransform::NodeTransform(TransformType whatType, PPoint3f point3f){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = point3f;
}

//for gl rotate
NodeTransform::NodeTransform(TransformType whatType, PPoint4f point4f){
	nodeType = transformation;
	transformationType = whatType;
	amount4 = point4f;
}

NodeTransform::NodeTransform(TransformType whatType)
{
	nodeType = transformation;
	transformationType = whatType;

	if (whatType == Translate)
	{
		amount3.x = 0.0f;
		amount3.y = 0.0f;
		amount3.z = 0.0f;
	} else if (whatType == Scale)
	{
		amount3.x = 1.0f;
		amount3.y = 1.0f;
		amount3.z = 1.0f;
	} else if (whatType == Rotate)
	{
		amount4.w = 0.0f;
		amount4.x = 0.0f;
		amount4.y = 0.0f;
		amount4.z = 0.0f;
	}
}

void NodeTransform::nodeSpecificCodeDown(){
	switch (transformationType){
	case Translate:
		glTranslatef(amount3.x, amount3.y, amount3.z);
		break;
	case Rotate:
		glRotatef(amount4.w, amount4.x, amount4.y, amount4.z);
		break;
	case Scale:
		glScalef(amount3.x, amount3.y, amount3.z);
		break;
	}
}
