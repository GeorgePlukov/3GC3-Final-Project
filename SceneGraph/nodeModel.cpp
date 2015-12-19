#include "nodeModel.h"
#include "../includes.h"

NodeModel::NodeModel(ModelType whatType)
{
	nodeType = model;
	modelType = whatType;
	this->m = NULL;
	isDrawable = true;
}

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

	switch (modelType) {
	case Helicopter:
		//TODO
		break;
	case Ground:
		drawGround();
		break;
	case Building:
		georgeSolidCube();
		break;
	case Target:
		//TODO
		break;
	}
}
void NodeModel::georgeSolidCube() {

	glBegin(GL_QUADS);

	//front

	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, 1);

	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, 1);

	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);

	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);

	//top
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 1);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, -1);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);

	//bottom
	glNormal3f(0, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, 1);

	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, 1);

	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);

	glNormal3f(0, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, -1);

	//left side
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);

	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 1);

	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, -1);

	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);

	//right side
	glNormal3f(1, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);

	glNormal3f(1, 0, 0);
	glVertex3f(1, -1, 1);

	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);

	glNormal3f(1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);

	//back side

	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, -1);

	glNormal3f(0, 0, -1);
	glVertex3f(-1, -1, -1);

	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);

	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);

	glEnd();
}

void NodeModel::drawGround()
{
	int size = 300;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size * 2; z++)
		{
			glNormal3f(0, 1, 0.5);
			glTexCoord2f(1, 0);
			glVertex3f(x - size / 2, 1.0f, -z + size / 2);

			glNormal3f(0, 1, 0.5);
			glTexCoord2f(0, 0);
			glVertex3f(x + 1 - size / 2, 1.0f, -z + size / 2);

			glNormal3f(0, 1, 0.5);
			glTexCoord2f(0, 1);
			glVertex3f(x + 1 - size / 2, 1.0f, -z - 1 + size / 2);

			glNormal3f(0, 1, 0.5);
			glTexCoord2f(1, 1);
			glVertex3f(x - size / 2, 1.0f, -z - 1 + size / 2);
		}
	}
	glEnd();
}