#include "nodeTransform.h"

//for gltranslate and gl scale
NodeTransform::NodeTransform(transformType whatType, PPoint3f point3f){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = point3f;
}

//for gl rotate
NodeTransform::NodeTransform(transformType whatType, PPoint4f point4f){
	nodeType = transformation;
	transformationType = whatType;
	amount4 = point4f;
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
