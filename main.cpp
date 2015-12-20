#include "includes.h"

const int WIDTH = 900;
const int HEIGHT = 600;
const float ASPECT = WIDTH / HEIGHT;

/* Rotations on the 3 axes */
float xRotation = 0, yRotation = 0, zRotation = 0;

/* Starfox Utils */
StarfoxUtils utils;

/* The 6 direction vectors */
PVector3f forwardVec(0, 0, -1);
PVector3f backVec = -forwardVec;
PVector3f upVec(0, 1, 0);
PVector3f downVec = -upVec;
PVector3f leftVec = upVec * forwardVec;
PVector3f rightVec = -leftVec;

/* Camera Vector for translations */
PVector3f cam(0.0f, 12.0f, 75.0f);

const float cameraSpeed = 0.5f;
const float mouseSensitivity = 0.01;

/* Light Items */
Light *light1;

/* Material Definitions*/
Material *m1;

/* Scene Graph*/
#include "SceneGraph/sceneGraph.h"
SceneGraph *SG;
/* Texture */
GLubyte* woodTex, *legoSideTex, *legoTopTex;
int width, height, maks;
GLuint textures[5];

/* Node ID's */
int masterID = 0;
int getID() {
	return masterID++;
}

void generateGround() 
{
	NodeGroup *group;
	NodeTransform *rotation, *scale, *translation;
	NodeModel *model;
	/*Initially, draw ground*/
	group = new NodeGroup();
	SG->insertChildNodeHere(group);
	SG->goToChild(0);

	/* Apply scaling to ground*/
	scale = new NodeTransform(Scale);
	SG->insertChildNodeHere(scale);
	SG->goToChild(0);

	/* Apply translation to ground*/
	translation = new NodeTransform(Translate);
	SG->insertChildNodeHere(translation);
	SG->goToChild(0);

	/* Draw Ground*/
	model = new NodeModel(Ground, textures[0]);
	SG->insertChildNodeHere(model);

	SG->goToRoot();
}

void generateRandomBuildings(int numOfBuildings)
{
	NodeGroup *group;
	NodeTransform *rotation, *scale, *translation;
	NodeModel *model;

	/* Add 10 buildings for now */
	for (int i = 1; i <= numOfBuildings; i++)
	{
		group = new NodeGroup();
		SG->insertChildNodeHere(group);
		SG->goToChild(i);

		/* Apply scaling to each model*/
		scale = new NodeTransform(Scale, utils.getRandomBuildingScaling());
		SG->insertChildNodeHere(scale);
		SG->goToChild(0);

		/* Apply translation to each model*/
		translation = new NodeTransform(Translate, utils.getRandomBuildingTranslation());
		SG->insertChildNodeHere(translation);
		SG->goToChild(0);

		/* Draw each model */
		model = new NodeModel(Building, textures[1]);
		SG->insertChildNodeHere(model);

		SG->goToRoot();
	}
}

/* Moves camera positions along a vector*/
void moveCamera(PVector3f v, float amt)
{
	cam = cam + (v * amt);
}

void checkForCrash()
{

}

/*
	Sets up the camera, lighting and materials,
	then calls the draw function
*/
void display()
{
	/* Clear the Screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*6 DOF camera controls*/
	glTranslatef(-cam.x, -cam.y, -cam.z);

	glRotatef(-xRotation, 1, 0, 0);
	glRotatef(-yRotation, 0, 1, 0);
	glRotatef(-zRotation, 0, 0, 1);

	//light1->enable();

	SG->draw();
	SG->moveAllBuildingsForward();
	checkForCrash();

	glutSwapBuffers();

	glutPostRedisplay();
}

void lockCamera()
{

	if (cam.x < -10.0f)
		cam.x = -10.0f;
	if (cam.x > 10.0f)
		cam.x = 10.0f;
	if (cam.y < 5.0f)
		cam.y = 5.0f;
	if (cam.y > 10.0f)
		cam.y = 10.0f;

	if (zRotation < -20.0f)
		zRotation = -20.0f;
	if (zRotation > 20.0f)
		zRotation = 20.0f;

}

/* kbd -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	/*Esc to exit the program*/
	if (key == 27 || key == 'q')
	{
		exit(0);
	}

	else if (key == 'w')
	{
		moveCamera(upVec, cameraSpeed);
		SG->getAllBuildingLocations();
		//xRotation++;
	} else if (key == 'a')
	{
		moveCamera(leftVec, cameraSpeed);
		zRotation ++;
	} else if (key == 'r')
	{
		moveCamera(downVec, cameraSpeed);
		//xRotation--;
	} else if (key == 's')
	{
		moveCamera(rightVec, cameraSpeed);
		zRotation --;
	}

	lockCamera();
}


void special(int key, int x, int y) 
{
	switch (key) {
	/* Rotate Camera*/
	case GLUT_KEY_LEFT:
		zRotation--;
		break;
	case GLUT_KEY_RIGHT:
		zRotation++;
		break;
	case GLUT_KEY_UP:
		xRotation--;
		break;
	case GLUT_KEY_DOWN:
		xRotation++;
		break;
	}
}

void registerCallbacks()
{
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	//glutPassiveMotionFunc(mouseMotion);
}

void init()
{
	/*enable Z buffer test, otherwise things appear in the order they're drawn*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	//generate 2 texture IDs, store them in array "textures"
	glGenTextures(5, textures);

	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Set our perspective */
	gluPerspective(45.0f, ASPECT, 0.1f, 75.0f);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode(GL_MODELVIEW);

	/* Reset The View */
	glLoadIdentity();

	/* Colour of the background */
	glClearColor(0.0f, 0.75f, 1.0f, 1.0f);

	/* Define our lights */
	Param pos = {0.0f, 7.0f, 80.0f, 0.0f};
	Param spec = {0.9f, 0.9f, 0.9f, 1.0f};
	Param dif = {0.5f, 0.5f, 0.5f, 1.0f};
	Param amb = {0.1f, 0.2f, 0.1f, 1.0f};

	light1 = new Light(1, pos, dif, spec, amb);

	Param ambM = {0.05f, 0.0f, 0.0f, 1.0f};
	Param difM = {0.5f, 0.4f, 0.4f, 1.0f};
	Param specM = {0.7f, 0.04f, 0.04f, 1.0f};
	float reflect = 0.78125f;
	m1 = new Material(difM, specM, ambM, reflect);
	
	light1->enable();
	//m1->enable();
	// Create an instance of ppm loader
	PPMLoader *ppm = new PPMLoader();
	// LOAD TEXTURE
	woodTex = ppm->loadPPM("textures/wood2.ppm", &width, &height, &maks);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodTex);

	// LOAD TEXTURE
	legoSideTex = ppm->loadPPM("textures/lego.ppm", &width, &height, &maks);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, legoSideTex);

	SG = new SceneGraph();
	generateGround();
	generateRandomBuildings(20);
}

void printStartMenu()
{
	printf("\033[H\033[J");
	printf("***********************************\n");
	printf("****           TITLE            ***\n");
	printf("***********************************\n");
	printf("\n");

}

void centerScreen()
{
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
	                       (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
}

int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	centerScreen();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TITLE");

	init();

	registerCallbacks();
	//printStartMenu();

	//start the program!
	glutMainLoop();

	return 0;
}
