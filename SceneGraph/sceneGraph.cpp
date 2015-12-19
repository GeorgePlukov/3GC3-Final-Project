#include "sceneGraph.h"
#include "../includes.h"

SceneGraph::SceneGraph()
{
	rootNode = new Node();
	currentNode = rootNode;
	printf("scene graph init done\n");
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot()
{
	currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i)
{
	if (i < currentNode->children->size() && i >= 0)
	{
		currentNode = currentNode->children->at(i);
	}
	else
	{
		printf("child out of range");
	}
}

void SceneGraph::goToParent()
{
	if (currentNode->parent != 0)
	{
		currentNode = currentNode->parent;
	}
}

/* Inserts a child node into the current node */
void SceneGraph::insertChildNodeHere(Node *node)
{
	currentNode->children->push_back(node);
	/* Make this node the parent of the child!! */
	currentNode->children->at(currentNode->children->size()-1)->parent = currentNode;
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode()
{
	if (currentNode->children->size() > 0)
	{
		printf("Deletion Error: Can only delete leaf nodes\n");
	} else
	{
		int childID = currentNode->ID;
		goToParent();
		if (currentNode->children->size() == 1)
		{
			currentNode->children->pop_back();
			deleteThisNode();
		} else
		{
			int size = currentNode->children->size();
			for (int i = 0; i < size; i++)
			{
				if (currentNode->children->at(i)->ID == childID)
				{
					currentNode->children->erase(currentNode->children->begin()+i);
					break;
				}
			}
		}
	}
}

void SceneGraph::replaceThisNode(Node *node)
{
	if (node->children->size() > 0)
	{
		printf("Cannot replace this node with a parent node\n");
	} else
	{
		/* move children of this node to new node */
		for (int i = 0; i < currentNode->children->size(); ++i)
		{
			node->children->push_back(currentNode->children->at(i));
		}

		/* Set id of this node to new node */
		node->ID = currentNode->ID;

		goToParent();

		/* Delete old node */
		if (currentNode->children->size() == 1)
		{
			currentNode->children->pop_back();
		} else
		{
			int size = currentNode->children->size();
			for (int i = 0; i < size; i++)
			{
				if (currentNode->children->at(i)->ID == node->ID)
				{
					currentNode->children->erase(currentNode->children->begin()+i);
					break;
				}
			}
		}

		/* Push new node in place of old node */
		currentNode->children->push_back(node);
	}
}

void SceneGraph::deleteBuildings()
{
	goToRoot();
	if (currentNode->children->size() > 1)
	{
		currentNode->children->erase(currentNode->children->begin()+1, currentNode->children->end());
	}
}

//draw the scenegraph
void SceneGraph::draw()
{
	rootNode->draw();
}