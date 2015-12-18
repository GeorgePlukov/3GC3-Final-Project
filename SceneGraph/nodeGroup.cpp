#include "nodeGroup.h"
#include "../includes.h"
NodeGroup::NodeGroup()
{
	nodeType = group;
}

void NodeGroup::nodeSpecificCodeDown()
{
	glPushMatrix();
}

void NodeGroup::nodeSpecificCodeUp()
{
	glPopMatrix();
}