#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include <cstdio>
#include "node.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"
#include "../StarfoxUtils.h"

class SceneGraph
{
public:
	SceneGraph();	//constructor

	//Scene Graph Navigation
	void goToRoot();
	void goToChild(int i);
	void goToParent();
	void insertChildNodeHere(Node *node);
	void deleteThisNode();
	void replaceThisNode(Node *node);
	void deleteBuildings();
	void moveAllBuildingsForward();
	//Scene Graph Draw
	void draw();
	NodeTransform* getCurrentTransformNode();


private:
	Node *rootNode;
	Node *currentNode;
	StarfoxUtils utils;
};

#endif