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
		for (int i = 0; i < currentNode->children->size(); i++)
		{
			node->children->push_back(currentNode->children->at(i));
		}
	
		/* Set id of this node to new node */
		node->ID = currentNode->ID;

		goToParent();

		/* Delete old node of parent */
		if (currentNode->children->size() == 1)
		{
			currentNode->children->pop_back();
		} else
		{
			for (int i = 0; i < currentNode->children->size(); i++)
			{
				if (currentNode->children->at(i)->ID == node->ID)
				{
					currentNode->children->erase(currentNode->children->begin()+i);
					break;
				}
			}
		}

		/* Push new node in place of old node */
		insertChildNodeHere(node);
		goToChild(currentNode->children->size()-1);
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

void SceneGraph::moveAllBuildingsForward()
{
	goToRoot();
	/* Loop through all the building children */
	for (int i = 1; i < currentNode->children->size(); i++)
	{
		/* Go to Building group node*/
		goToChild(i);
		/* Go to transform node... 2 down from the group node */
		for (int j = 0; j < 2; j++)
		{
			goToChild(0);
		}
		NodeTransform *translationNode = (NodeTransform*) currentNode;
		translationNode->amount3.z ++;
		/* If we have passed the building, move it somewhere else behind the clipping plane*/
		if (translationNode->amount3.z > 70)
		{
			translationNode->amount3 = utils.getRandomBuildingTranslation();
		}
		goToRoot();
	}
}

std::vector<PPoint3f> SceneGraph::getAllBuildingLocations()
{
	std::vector<PPoint3f> buildingTranslations = getAllBuildingTranslations();
	std::vector<PPoint3f> buildingScales = getAllBuildingScales();

	std::vector<PPoint3f> buildingLocations;

	int size = buildingScales.size();
	
	for (int i = 0; i < size; i++)
	{
		PPoint3f location = buildingTranslations[i];
		location.y = buildingScales[i].y;
		buildingLocations.push_back(location);
	}

	return buildingLocations;


}

std::vector<PPoint3f> SceneGraph::getAllBuildingTranslations()
{
	std::vector<PPoint3f> buildingTranslations;

	goToRoot();
	/* Loop through all the building children */
	for (int i = 1; i < currentNode->children->size(); i++)	
	{
		/* Go to Building group node*/
		goToChild(i);
		/* Go to transform node... 2 down from the group node */
		for (int j = 0; j < 2; j++)
		{
			goToChild(0);
		}
		NodeTransform *translationNode = (NodeTransform*) currentNode;

		buildingTranslations.push_back(translationNode->amount3);
		goToRoot();
	}

	return buildingTranslations;

}

std::vector<PPoint3f> SceneGraph::getAllBuildingScales()
{
	std::vector<PPoint3f> buildingScales;

	goToRoot();
	/* Loop through all the building children */
	for (int i = 1; i < currentNode->children->size(); i++)	
	{
		/* Go to Building group node*/
		goToChild(i);
		/* Go to scale node... 1 down from the group node */
		goToChild(0);


		NodeTransform *scaleNode = (NodeTransform*) currentNode;
		buildingScales.push_back(scaleNode->amount3);
		goToRoot();
	}

	return buildingScales;
}

//draw the scenegraph
void SceneGraph::draw()
{
	rootNode->draw();
}