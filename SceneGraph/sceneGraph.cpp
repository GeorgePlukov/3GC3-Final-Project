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
		if (translationNode->amount3.z > 76)
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

void SceneGraph::destroyBuilding(int x, int y)
{
	printf("attempting to destroy building \n");
	/* Allocate matricies memory */
	double matModelView[16], matProjection[16];
	int viewport[4];

	/* Grab the matricies */
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* Unproject the values */
	double winX = (double)x;
	double winY = viewport[3] - (double)y;

	double start[] = {0,0,0};
	double end[] = {1,1,1};

	/* Get point on the 'near' plane */
	gluUnProject(winX, winY, 0.0, matModelView, matProjection,
         viewport, &start[0], &start[1], &start[2]);

	/* Get point on the 'near' plane */
	gluUnProject(winX, winY, 1.0, matModelView, matProjection,
         viewport, &end[0], &end[1], &end[2]);

	/* Make the start and ends PPoint3fs*/
	PPoint3f startPoint(start[0], start[1], start[2]);
	PPoint3f endPoint(end[0], end[1], end[2]);
	/* Get ray direction */
	PVector3f rayDirection(startPoint, endPoint);
	rayDirection.normalize();

	NodeTransform *scale, *translate;
	int id = 0;
	double smallestTmin = 1000000;

	goToRoot();

	for (int i = 1; i < currentNode->children->size(); i++)
	{
		/* This is the group node of the building */
		goToChild(i);
		/* This is the scale node of the building */
		goToChild(0);
		scale = (NodeTransform*) currentNode;
		/* This is the translation node of the building*/
		goToChild(0);
		translate = (NodeTransform*) currentNode;
		/* This is the model node of the building */
		goToChild(0);
		id = currentNode->ID;
		

		PPoint3f min;
		min.x = translate->amount3.x - 0.5;
		min.y = translate->amount3.y + 0.5;
		min.z = translate->amount3.z - 0.5;

		PPoint3f max;
		max.x = translate->amount3.x + 0.5;
		max.y = (translate->amount3.y - 0.5) + (scale->amount3.y / 2);
		max.z = translate->amount3.z + 0.5;

		/*
			Check to see if there is a collision with the current
			shape and the ray cast out;
		*/

		double tmin = (min.x - startPoint.x) / rayDirection.x;
		double tmax = (max.x - startPoint.x) / rayDirection.x;

		if (tmin > tmax){
			std::swap(tmin, tmax);
		}

		double tymin = (min.y - startPoint.y) / rayDirection.y;
		double tymax = (max.y - startPoint.y) / rayDirection.y;

		if (tymin > tymax){
			std::swap(tymin, tymax);
		}

		if ((tmin > tymax) || (tymin > tmax)) {
			goToRoot();
			continue; // no intersection point continue to next bounded box
		}

		if (tymin > tmin) {
			tmin = tymin;
		}

		if (tymax < tmax){
			tmax = tymax;
		}

		double tzmin = (min.z - startPoint.z) / rayDirection.z;
		double tzmax = (max.z - startPoint.z) / rayDirection.z;

		if (tzmin > tzmax){
			std::swap(tzmin, tzmax);
		}

		if ((tmin > tzmax) || (tzmin > tmax)){
			continue; // no intersection point continue to next bounded box
		}

		if (tzmin > tmin){
			tmin = tzmin;
		}

		if (tzmax < tmax){
			tmax = tzmax;
		}

		//There is an intersection point. Now we want to check if it is the closest intersection point to our ray.
		//If so then remove the previous intersection point and set it to this new intersection point.
		if (tmin < smallestTmin){
			smallestTmin = tmin;
		}
		goToRoot();
	}
	printf("Shape HIT! ID: %d\n", id);
	scale->amount3.y -= 6;
	//translate->amount3 = utils.getRandomBuildingTranslation();


}

//draw the scenegraph
void SceneGraph::draw()
{
	rootNode->draw();
}