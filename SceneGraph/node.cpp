#include "node.h"
#include <stdio.h>
#include "../includes.h"
Node::Node()
{	
	ID = getID();
	nodeType = root; 
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;
	printf("node init done\n");
}

//==================================================================
//function which does all the heavy lifting
void Node::draw()
{
	nodeSpecificCodeDown();

	const int numberOfChildren = children->size();
	if (numberOfChildren > 0)
	{
		for (int i = 0; i < numberOfChildren; i++)
		{
			children->at(i)->draw();
		}
	}

	nodeSpecificCodeUp();
}

//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN 
//DERIVED CLASSES

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}