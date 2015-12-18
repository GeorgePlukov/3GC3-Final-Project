#include "nodeModel.h"
#include "../includes.h" 
NodeModel::NodeModel(ModelType whatType, Material *m)
{
	nodeType = model;
	modelType = whatType;
	this->m = m;
	isDrawable = true;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown()
{
		
	switch (modelType){
	case Sphere:
		glutSolidSphere(1, 12, 10);
		break;
	case Cube:
		glutSolidCube(1);
		break;
	case Teapot:
		glutSolidTeapot(1);
		break;
	case Custom:
		//own mesh thing
		break;
	}
}