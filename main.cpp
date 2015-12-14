
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
// DEFINITIONS
///////////////////////////////////////////////////////////////
#define FRAME_WIDTH 600
#define FRAME_HEIGHT 600


///////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////////

// Camera *camera1 = NULL;
// float camPos[] = {10, 10, 10};

Light *light1 = NULL;
Light *light2 = NULL;
int currentLight = 0;
int numberOfLights = 2;

// // Scenegraph Variables
// SceneGraph *SG;
// Serializer *serializer;
// int masterID = 0;

int currentMat = 0;
int numberOfMat = 5; // 0 + 4
Material m, m1, m2, m3, m4;

int currentObject;

///////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
///////////////////////////////////////////////////////////////

// int getID() {
// 	return masterID++;
// }
///////////////////////////////////////////////////////////////
// SCENE GRAPH HELPER FUNCTIONS
///////////////////////////////////////////////////////////////
// Adding an object to the scene graph requires a couple properties
// First add a transition that starts empty ie move by (0,0,0)
// If anything such as rotation or other methods to move or alter the model itself
// that should be rendered in the scene graph then it would be added here as an additional node
// Then add the model
// void addObject(ModelType type) {
// 	SG->goToRoot();
// 	Vector3D tempVec3;
// 	tempVec3.x = 0;
// 	tempVec3.y = 0;
// 	tempVec3.z = 0;
// 	// Add the empty transform node
// 	NodeTransform *t1 = new NodeTransform(Translate, tempVec3);
// 	SG->insertChildNodeHere(t1);

// 	// go to the transforms child
// 	SG->goToChild(currentObject);
// 	Material cur;
// 	// Select the proper material
// 	switch (currentMat) {
// 	case 0:
// 		cur = m;
// 		break;
// 	case 1:
// 		cur = m1;
// 		break;
// 	case 2:
// 		cur = m2;
// 		break;
// 	case 3:
// 		cur = m3;
// 		break;
// 	case 4:
// 		cur = m4;
// 		break;

// 	}

// 	// Select what node should be added to the scene graph
// 	NodeModel *n;
// 	switch (type) {
// 	case Plane:
// 		n = new NodeModel(Plane, cur);
// 		break;
// 	case Cube:
// 		n = new NodeModel(Cube, cur);
// 		break;
// 	case Teapot:
// 		n = new NodeModel(Teapot, cur);
// 		break;
// 	case Sphere:
// 		n = new NodeModel(Sphere, cur);
// 		break;
// 	case Torus:
// 		n = new NodeModel(Torus, cur);
// 		break;
// 	case Cone:
// 		n = new NodeModel(Cone, cur);
// 		printf("wtf\n");
// 		break;
// 	default:
// 		break;
// 	}
// 	SG->insertChildNodeHere(n);

// 	// increment the current obj counter
// 	currentObject++;
// }
// void movObject(int id, float x, float y, float z) {
// 	SG->goToRoot();
// 	// Navigate to the correct child selected by ray casting
// 	SG->goToChild(id);

// 	// Create a new node  based off the old node
// 	Node * cN = SG->getCurrentNode();
// 	//Transform the new node
// 	cN->transformAct(x, y, z);

// 	// Swap that shit bitch
// 	SG->swapCurrentWith(cN);

// }
////////////////////////////////////////////////////////
// IO HANDLERS
////////////////////////////////////////////////////////
void keyboardHandler(unsigned char key, int xIn, int yIn) {

	switch (key) {
	// Quit the program
	case 'q':
		exit(0);
	// // Reset the scene to blank
	// case 'r':
	// 	SG = new SceneGraph();
	// 	currentObject = 0;
	// 	addObject(Plane);
	// 	break;
	// // Switch through the materials
	// case 'm':
	// 	currentMat = (currentMat + 1) % numberOfMat;
	// 	break;
	// // Switch between the light sources
	// case 'y':
	// 	currentLight = (currentLight + 1) % numberOfLights;
	// 	break;
	// // Load a scene from save file
	// case 'l':
	// 	break;
	// // Save the current scene to a file
	// case 'k':
	// 	serializer->serializeSceneGraph();
	// 	break;
	// case 'w':
	// 	movObject(currentObject - 1, 1.0f, 0.0f, 0.0f);
	// 	break;
	// case 'a':
	// 	movObject(currentObject - 1, 0.0f, 0.0f, 1.0f);
	// 	break;
	// case 's':
	// 	movObject(currentObject - 1, -1.0f, 0.0f, 0.0f);
	// 	break;
	// case 'd':
	// 	movObject(currentObject - 1, 0.0f, 0.0f, -1.0f);
	// 	break;
	// case '1':
	// 	addObject(Cube);
	// 	break;
	// case '2':
	// 	addObject(Teapot);
	// 	break;
	// case '3':
	// 	addObject(Sphere);
	// 	break;
	// case '4':
	// 	addObject(Torus);
	// 	break;
	// case '5':
	// 	addObject(Cone);
	// 	break;
	}
	glutPostRedisplay();
}

// void special(int key, int x, int y) {
// 	/* arrow key presses move the camera */
// 	switch (key) {
// 	case GLUT_KEY_LEFT: 	camera1->decreaseX(1); break;
// 	case GLUT_KEY_RIGHT: 	camera1->increaseX(1); break;
// 	case GLUT_KEY_UP: 		camera1->decreaseZ(1); break;
// 	case GLUT_KEY_DOWN: 	camera1->increaseZ(1); break;
// 	case GLUT_KEY_HOME: 	camera1->decreaseY(1); break;
// 	case GLUT_KEY_END: 		camera1->increaseY(1); break;

// 	}
// 	glutPostRedisplay();
// }

void displayHandler(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Make the camera look at the origin point
	camera1->lookHere();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.reflect);
	glClearColor(0.3, 0.3, 0.7, 1);

	light1->enable();
	light2->enable();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Draw the scenegraph that contains all of the objects in the scene
	SG->draw();


	glutSwapBuffers();
}



///////////////////////////////////////////////////////////////
// INIT
///////////////////////////////////////////////////////////////

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_FLAT);


	// Initialize all class variables
	camera1 = new Camera(10.0f, 10.0f);


	Param pos = { 10.0f, 10.0f, 10.0f, 1.0f};
	Param spec = {0.9f, 0.9f, 0.9f, 1.0f};
	Param dif = {0.5f, 0.5f, 0.5f, 1.0f};
	Param amb = {0.1f, 0.2f, 0.1f, 1.0f};
	light1 = new Light(0, pos, dif, spec, amb);

	Param pos2 = { -10.f, 10.0f, -10.0f, 1.0f};
	Param spec2 = {0.9f, 0.2, 0.2f, 1.0f};
	Param dif2 = {0.5f, 0.3f, 0.9f, 1.0f};
	Param amb2 = {0.1f, 0.2f, 0.3f, 1.0f};
	light2 = new Light(1, pos2, dif2, spec2, amb2);

	light1->enable();
	light2->enable();

	//////////// Mat
	m.dif[0] = 0.9f;
	m.dif[1] = 0.9f;
	m.dif[2] = 0.8f;
	m.dif[3] = 1.0f;

	m.amb[0] = 0.9f;
	m.amb[1] = 0.9f;
	m.amb[2] = 0.1f;
	m.amb[3] = 1.0f;

	m.spec[0] = 0.9f;
	m.spec[1] = 0.9f;
	m.spec[2] = 0.2f;
	m.spec[3] = 1.0f;

	m.reflect = 50.0f;
	////////////////// Mat 1
	m1.dif[0] = 0.5f;
	m1.dif[1] = 0.5f;
	m1.dif[2] = 0.5f;
	m1.dif[3] = 1.0f;

	m1.amb[0] = 0.2f;
	m1.amb[1] = 0.2f;
	m1.amb[2] = 0.2f;
	m1.amb[3] = 1.0f;

	m1.spec[0] = 0.9f;
	m1.spec[1] = 0.9f;
	m1.spec[2] = 0.2f;
	m1.spec[3] = 1.0f;

	m1.reflect = 10.0f;
	////////////////// mat 2
	m2.dif[0] = 0.1f;
	m2.dif[1] = 0.4f;
	m2.dif[2] = 0.1f;
	m2.dif[3] = 1.0f;

	m2.amb[0] = 0.6f;
	m2.amb[1] = 0.4f;
	m2.amb[2] = 0.6f;
	m2.amb[3] = 1.0f;

	m2.spec[0] = 0.9f;
	m2.spec[1] = 0.9f;
	m2.spec[2] = 0.2f;
	m2.spec[3] = 1.0f;

	m2.reflect = 50.0f;

	///////////////// Mat 3
	m3.dif[0] = 0.112f;
	m3.dif[1] = 0.3f;
	m3.dif[2] = 0.9f;
	m3.dif[3] = 1.0f;

	m3.amb[0] = 0.1f;
	m3.amb[1] = 0.2f;
	m3.amb[2] = 0.3f;
	m3.amb[3] = 1.0f;

	m3.spec[0] = 0.23f;
	m3.spec[1] = 0.2f;
	m3.spec[2] = 0.83f;
	m3.spec[3] = 1.0f;

	m3.reflect = 65.0f;

///////////////// Mat 4
	m4.dif[0] = 0.42f;
	m4.dif[1] = 0.1f;
	m4.dif[2] = 0.0f;
	m4.dif[3] = 1.0f;

	m4.amb[0] = 0.1f;
	m4.amb[1] = 0.4f;
	m4.amb[2] = 0.1f;
	m4.amb[3] = 1.0f;

	m4.spec[0] = 0.43f;
	m4.spec[1] = 0.1f;
	m4.spec[2] = 0.83f;
	m4.spec[3] = 1.0f;

	m4.reflect = 66.0f;
	SG = new SceneGraph();
	serializer = new Serializer(SG);

}

// Initialize the scene graph
void initSceneGraph() {
	// define the variabel that gets incremented everu time a new object gets added to the scene
	currentObject = 0;
	// Add initial objects to the screen
	addObject(Plane);
	addObject(Teapot);

	serializer->serializeSceneGraph();
}


void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
}

///////////////////////////////
// APPLICATION ENTRY POINT
///////////////////////////////

int main(int argc, char** argv) {


	// GLUT - Initialzation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	// GLUT - Window Configuration
	glutInitWindowSize(FRAME_WIDTH, FRAME_HEIGHT);
	glutInitWindowPosition(50, 50);

	// Initialize Application Environment

	// Register Application Handlers
	glutCreateWindow("Scene Raycasting");
	glutDisplayFunc(displayHandler);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	printf("INSTRUCTIONS FOR USE: I changed some commands to make it a bit easier to use\n");
	printf("Load and save:\n");
	printf("k: save into a file\n");
	printf("l: load from a file\n");

	printf("Placeing objects\n");
	printf("1: place a cube\n");
	printf("2: Place a Teapot\n");
	printf("3: place a sphere\n");
	printf("4: Place a Torus\n");
	printf("5: Place a cone\n");

	printf("Material Change:\n");
	printf("Press m to toggle through the materials, it will change the material of the next item\n");

	printf("Moving objects\n");
	printf("wasd: Use wasd keys to move the object in the x, and z axies\n");

	printf("Light Source movement\n");
	printf("y: toggle between light sources\n");
	printf("u/i: x axis of movement\n");
	printf("o/p: y axis of movement\n");
	printf("[/]: z axis of movement\n");




	init();
	initSceneGraph();

	// Begin GLUT Application Loop
	glutMainLoop();
	return (0);
}