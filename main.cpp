#include "includes.h"

const int WIDTH = 900;
const int HEIGHT = 600;
const float ASPECT = WIDTH / HEIGHT;

/* Rotations on the 3 axes */
float xRotation = 0, yRotation = 0, zRotation = 0;

/* The 6 direction vectors */
PVector3f forwardVec(0, 0, -1);
PVector3f back = -forwardVec;
PVector3f up(0, 1, 0);
PVector3f down = -up;
PVector3f left = up * forwardVec;
PVector3f right = -left;

/* Camera Vector for translations */
PVector3f cam(0.0f, 7.0f, 75.0f);

const float cameraSpeed = 0.5f;
const float mouseSensitivity = 0.01;

/* Light Items */
Light *light1;

/* Material Definitions*/
Material *m1;

/* Scene Graph*/
#include "SceneGraph/sceneGraph.h"
SceneGraph *SG;

/* Node ID's */
int masterID = 0;
int getID() {
	return masterID++;
}

/***************************************************************************************/

//function which will populate a sample graph
void initGraph() {
	//temporary place which holds out values
	PPoint3f tmpPoint3f;


	//TRANSFORMATION
	//a tranlation transformation node
	//how much translation
	tmpPoint3f.x = 5.0f;
	tmpPoint3f.y = 3.0f;
	tmpPoint3f.z = -10.0f;
	//add the node as a child of root node
	NodeTransform *T1 = new NodeTransform(Translate, tmpPoint3f);
	//insert the node into the graph
	SG->insertChildNodeHere(T1);
	//go to the child node
	SG->goToChild(0);


	//MODEL
	//we will now add a teapot model to the graph as a child of the
	//transformation node
	// NodeModel *M1 = new NodeModel(Teapot, m1);
	//insert the node into the graph
	// SG->insertChildNodeHere(M1);


	//THE SAME FLOW CAN BE USED TO DYNAMICALLY ADD NODES
	//DURING RUNTIME
}


/***************************************************************************************/

void drawGround()
{
	int size = 300;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size * 2; z++)
		{
			glNormal3f(0, 1, 0);
			glVertex3f(x - size / 2, 1.0f, -z + size / 2);
			glNormal3f(0, 1, 0);
			glVertex3f(x + 1 - size / 2, 1.0f, -z + size / 2);
			glNormal3f(0, 1, 0);
			glVertex3f(x + 1 - size / 2, 1.0f, -z - 1 + size / 2);
			glNormal3f(0, 1, 0);
			glVertex3f(x - size / 2, 1.0f, -z - 1 + size / 2);
		}
	}
	glEnd();

}

void drawCubes()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 150; i += 10)
	{
		glPushMatrix();
		float z = 70.0f - (float)i;
		glTranslatef(5.0f, 2.0f, z);
		glutSolidCube(1);
		glPopMatrix();
	}

}

/* Moves camera positions along a vector*/
void moveCamera(PVector3f v, float amt)
{
	cam = cam + (v * amt);
	if (cam.z < -5.0f)
	{
		cam.z = 75.0f;
	}
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


	glPushMatrix();

	drawGround();
	drawCubes();
	// moveCamera(forwardVec, cameraSpeed);

	glPopMatrix();

	glPushMatrix();

	light1->enable();

	SG->draw();
	glPopMatrix();

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
		moveCamera(up, cameraSpeed);
		//xRotation++;
	} else if (key == 'a')
	{
		moveCamera(left, cameraSpeed);
		zRotation --;
	} else if (key == 'r')
	{
		moveCamera(down, cameraSpeed);
		//xRotation--;
	} else if (key == 's')
	{
		moveCamera(right, cameraSpeed);
		zRotation ++;
	}

	lockCamera();
}


void special(int key, int x, int y) {
	/* Use the arrow keys to move the selected light source around*/
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

	printf("Rotation: (%f, %f, %f)\n", xRotation, yRotation, zRotation);
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

	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Set our perspective */
	gluPerspective(45.0f, ASPECT, 0.1f, 100.0f);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode(GL_MODELVIEW);

	/* Reset The View */
	glLoadIdentity();

	/* Colour of the background */
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Define our lights
	Param pos = {0.0f, 1.0f, 80.0f, 1.0f};
	Param spec = {1.0f, 1.0f, 1.0f, 1.0f};
	Param dif = {0.0f, 0.0f, 0.0f, 1.0f};
	Param amb = {1.0f, 1.0f, 1.0f, 1.0f};
	light1 = new Light(1, pos, dif, spec, amb);

	Param ambM = {0.05f, 0.0f, 0.0f, 1.0f};
	Param difM = {0.5f, 0.4f, 0.4f, 1.0f};
	Param specM = {0.7f, 0.04f, 0.04f, 1.0f};
	float reflect = 0.78125f;
	m1 = new Material(difM, specM, ambM, reflect);
	light1->enable();

	m1->enable();

	SG = new SceneGraph();
	initGraph();

}

void printStartMenu()
{
	// printf("\033[H\033[J");
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
	printStartMenu();

	//start the program!
	glutMainLoop();

	return 0;
}
