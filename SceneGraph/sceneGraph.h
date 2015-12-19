#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include <cstdio>
#include "node.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"

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
	//Scene Graph Draw
	void draw();


private:
	Node *rootNode;
	Node *currentNode;
};

#endif