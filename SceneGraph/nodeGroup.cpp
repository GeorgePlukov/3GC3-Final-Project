#include "nodeGroup.h"

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