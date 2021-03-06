#include "includes.h"

const int WIDTH = 900;
const int HEIGHT = 600;
const float ASPECT = WIDTH / HEIGHT;

enum State {MAIN, GAME, LEADERBOARD};
State currentState = MAIN;

bool paused = false;
bool dead = false;
// Text for the main screen of the game

string game = "ButFox";
string pause = "PAUSED";
string menu [3] = {"1. Play", "2. Leaderboard", "ESC. Quit"};
string leaderboardTitle = "LeaderBoard";
string goBack = "Press b to go back";
string lowScore = "Score not high enough!";
string cont = "Press space to continue";

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
bool leftMove = false;
bool upMove = false;
bool downMove = false;
bool rightMove = false;


/* Camera Vector for translations */
PVector3f cam(0.0f, 12.0f, 75.0f);

const float cameraSpeed = 0.1f;
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
int scorecounter = 0;
bool countScore = true;
GLuint textures[5];

/* Scoreboard */
int currentScore = 0;
int highScore[3] = {12026, 11304, 4514};
string highNames[3] = {"George", "Philip ", "George"};

/* Shooting the laser goon */
bool spaceBarDown = false;
int shootCount = 0;

/* Node ID's */
int masterID = 0;
int getID() {
	return masterID++;
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

#include <sstream>
template <typename T>
std::string to_string(T value)
{
	//create an output string stream
	std::ostringstream os ;

	//throw the value into the string stream
	os << value ;

	//convert the string stream into a string and return
	return os.str() ;
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
	std::vector<PPoint3f> buildingLocations = SG->getAllBuildingLocations();

	const float EPSILON = 15.0f;

	for (int i = 0; i < buildingLocations.size(); i++)
	{
		if (buildingLocations[i].z > 75)
		{

			if (fabs(buildingLocations[i].x - cam.x) < 1.0f)
			{
				if (cam.y < buildingLocations[i].y)
				{
					dead = true;
					break;
				}
			}


		}
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
	string a = "Score:";

	// Determine what state should be drawn for the game
	switch (currentState) {
	case MAIN:

		/********** ALL DRAWING FOR SCOREBOARD **************/

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		// glRasterPos2i(100, 100);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.8, 0.2, 0.3);

		glTranslatef(WIDTH / 2 - 200, HEIGHT / 2 + 200, 0);
		glScalef(0.4f, 0.4f, 0.0f);
		/********** Leaderboard title **************/
		for (int i = 0; i < game.size(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, game.at(i));
		glPopMatrix();

		/*********** Player names and scores *************/
		for (int s = 0; s < 3; s++) {
			glPushMatrix();
			glTranslatef(WIDTH / 2 - 200, HEIGHT / 2 - ((s + 1) * 100) + 200, 0);
			glScalef(0.4f, 0.4f, 0.0f);

			for (int i = 0; i < menu[s].size(); i++) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, menu[s].at(i));
			}
			glPopMatrix();
		}

		// Return our view state back to what it needs to be for 3d drawing
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		break;

	/**********************************
	*
	*
	* Controls All game state display items
	*
	*
	***********************************/
	case GAME:
		if (dead) {
			paused = true;
			pause = "DEAD. you dead";
		}
		if (!paused) {

			// Check if the score should be updated
			if (countScore) {
				// add to the score
				currentScore += 1;
				countScore = false;
			}
			if (scorecounter % 10 == 0) {
				countScore = true;
			}
			scorecounter++;

			// Increase the counr of the laser fire
			if (spaceBarDown) {
				if (!(shootCount > 50)) {
					shootCount+=2;
				}
			}

			// Moves the camera based on what arrow keys
			//are currently being held down

			if (upMove) {
				moveCamera(upVec, cameraSpeed);
			}
			if (leftMove) {
				moveCamera(leftVec, cameraSpeed);
				zRotation ++;
			}
			if (downMove) {
				moveCamera(downVec, cameraSpeed);
			}
			if (rightMove) {
				moveCamera(rightVec, cameraSpeed);
				zRotation--;
			}
			lockCamera();

			SG->moveAllBuildingsForward();
			checkForCrash();

		}
		SG->draw();

		/******* Draw all the items that need a 2d projection to be drawn ********/
		// score, crosshair, paused menu
		// THis next part is used to display the current score while the game is active
		glMatrixMode(GL_PROJECTION);
		// Save our projection states
		glPushMatrix();
		glLoadIdentity();
		// switch too a 2d projection
		gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		// Draw the text to the screen
		glDisable(GL_LIGHTING);

		a = a + to_string(currentScore);
		glPushMatrix();
		glScalef(0.3f, 0.3f, 0.0f);

		// Draw the score
		for (int i = 0; i < a.size(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, a.at(i));

		glPopMatrix();

		// Draw the cross hair
		glLineWidth(2);
		glPushMatrix();
		glBegin(GL_LINES);
		// Top left line
		glVertex3f(WIDTH / 2 - 140, HEIGHT / 2 + 20, 0);
		glVertex3f(WIDTH / 2 - 25,  HEIGHT / 2 + 20, 0);
		// bottom ledt line
		glVertex3f(WIDTH / 2 - 140, HEIGHT / 2 - 20, 0);
		glVertex3f(WIDTH / 2 - 25,  HEIGHT / 2 - 20, 0);

		// top right line
		glVertex3f(WIDTH / 2 + 140, HEIGHT / 2 + 20, 0);
		glVertex3f(WIDTH / 2 + 25,  HEIGHT / 2 + 20, 0);
		// bottom right line
		glVertex3f(WIDTH / 2 + 140, HEIGHT / 2 - 20, 0);
		glVertex3f(WIDTH / 2 + 25,  HEIGHT / 2 - 20, 0);
		glEnd();
		// outer circles
		glBegin(GL_POLYGON);
		// draw a circular device
		for (int i = 0; i <= 200; i++) {
			glColor4f(0.2, 0.8, 0.3, 0.2f);
			glVertex2f(
			  WIDTH / 2  + (30 * cos(i *  3.14159265 / 100)),
			  HEIGHT / 2  + (30 * sin(i * 3.14159265 / 100))
			);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor4f(1.0, 0.3, 0.3, 0.5);
		glVertex2f(WIDTH - 70, 30);
		glVertex2f(WIDTH - 40, 30);
		glVertex2f(WIDTH - 40, 27 + 3 * shootCount);
		glVertex2f(WIDTH - 70, 27 + 3 * shootCount);

		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor4f(1.0, 0.3, 0.3, 1.0);

		glVertex2f(WIDTH - 70, 30);
		glVertex2f(WIDTH - 40, 30);
		glVertex2f(WIDTH - 40, 30 + 154);
		glVertex2f(WIDTH - 70, 30 + 154);
		glEnd();
		glPopMatrix();

		// DRAW PAUSED IF PAUSED
		if (paused) {

			glPushMatrix();
			glLineWidth(3);

			glTranslatef(80, -200, 0);

			glTranslatef(WIDTH / 2 - 275, HEIGHT / 2 + 300, 0);
			glScalef(0.4f, 0.4f, 0.0f);
			/********** Leaderboard title **************/
			for (int i = 0; i < pause.size(); i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, pause.at(i));
		}
		// if you dead say you dead
		if (dead) {

			glTranslatef(-1200, -200, 0);
			for (int i = 0; i < lowScore.size(); i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, lowScore.at(i));

			glTranslatef(-1600, -300, 0);
			for (int i = 0; i < cont.size(); i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, cont.at(i));
		}
		glPopMatrix();

		glLineWidth(1);
		// Restore the previous settings
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();


		break;
	case LEADERBOARD:

		/********** ALL DRAWING FOR SCOREBOARD **************/

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		// glRasterPos2i(100, 100);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(WIDTH / 2 - 200, HEIGHT / 2 + 200, 0);
		glScalef(0.4f, 0.4f, 0.0f);
		/********** Leaderboard title **************/
		for (int i = 0; i < leaderboardTitle.size(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, leaderboardTitle.at(i));
		glPopMatrix();

		/*********** Player names and scores *************/
		for (int s = 0; s < 3; s++) {
			glPushMatrix();
			glTranslatef(WIDTH / 2 - 200, HEIGHT / 2 - ((s + 1) * 100) + 200, 0);
			glScalef(0.4f, 0.4f, 0.0f);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, to_string(s + 1).at(0));
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '.');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');


			for (int i = 0; i < highNames[s].size(); i++) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, highNames[s].at(i));
			}

			glTranslatef(400, 0, 0);
			string str = to_string(highScore[s]);

			for (int i = 0; i < str.size(); i++) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
			}
			glPopMatrix();
		}


		/********** Go Back **************/
		glPushMatrix();

		glTranslatef(WIDTH / 2 - 250, 100, 0);
		glScalef(0.4f, 0.4f, 0.0f);
		for (int i = 0; i < goBack.size(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, goBack.at(i));

		}
		glPopMatrix();

		// Return our view state back to what it needs to be for 3d drawing
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glEnable(GL_LIGHTING);

		break;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

// Controls the wasd keys while the game is being played
void keyboard_downUp(unsigned char key, int x, int y) {
	// Toggles whether the keys are being held down or not
	if (key == 'w')
	{
		upMove = false;
		// SG->getAllBuildingLocations();
		//xRotation++;
	} else if (key == 'a') {
		leftMove = false;
	} else if (key == 's') {
		downMove = false;
	} else if (key == 'd') {
		rightMove = false;
	} else if (key == 32) {
		spaceBarDown = false;
		if (dead) {
			currentScore = 0;
			scorecounter = 0;
			shootCount = 0;
			dead = false;
			paused = false;
			SG->deleteBuildings();
			generateRandomBuildings(20);
			currentState = LEADERBOARD;
		}
		// SHOOT THA LASA
		if (shootCount > 50) {
			SG->destroyBuilding(cam.x, cam.y);
		}

		shootCount = 0;

	}

}
void gameKeyboard(unsigned char key, int x, int y) {

	// Toggles whether the keys are being held down or not
	if (key == 'w')
	{
		upMove = true;
		// SG->getAllBuildingLocations();
		//xRotation++;
	} else if (key == 'a') {
		leftMove = true;
		//xRotation++;
	} else if (key == 's') {
		downMove = true;
	} else if (key == 'd') {
		rightMove = true;
	} else if (key == 'p') {
		paused = !paused;
	} else if (key == 32) {
		spaceBarDown = true;
	}
}

void mainKeyboard(unsigned char key, int x, int y) {
	if (key == '1') {
		currentState = GAME;
	} else if (key == '2') {
		currentState = LEADERBOARD;
	}
}

void leaderboardKeyboard(unsigned char key, int x, int y) {
	if (key == 'b') {
		currentState = MAIN;
	}
}
/* kbd -- the GLUT keyboard function
 * key -- the key pressed
 * x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	/*Esc to exit the program*/
	if (key == 27) {
		exit(0);
	}
	switch (currentState) {
	case MAIN:
		mainKeyboard(key, x, y);
		break;
	case GAME:
		gameKeyboard(key, x, y);
		break;
	case LEADERBOARD:
		leaderboardKeyboard(key, x, y);
		break;
	}

	lockCamera();
}

void registerCallbacks()
{
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboard_downUp);
}

void init()
{
	/*enable Z buffer test, otherwise things appear in the order they're drawn*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
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
	printf("****          ButFox           ***\n");
	printf("***********************************\n");
	printf("Instructions:\n");
	printf("The point of this game is to get the highest score possible.\n");
	printf("Hitting the towers will kill you.\n");
	printf("\n");
	printf("Use you advanced flying techniques and epic pew pew laser gun\n");
	printf("to kill the towers and make your family proud!\n");
	printf("Controls:\n");
	printf("Press p to pause/resume during the game!\n");
	printf("Navigate the menus with the corepsponding number.\n");
	printf("Hit escape at anytime to exit the program\n");
	printf("Use the WASD keys to navigate the field and charge/fire the laser \n");
	printf("using the space bar.\n");
	printf("\n");
	printf("\n");
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
	printStartMenu();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("ButFox");

	init();

	registerCallbacks();
	printStartMenu();

	//start the program!
	glutMainLoop();

	return 0;
}
