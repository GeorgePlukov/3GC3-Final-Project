/* THese are all globals!! */

/* Rotations on the 3 axes */
/* Default values set by trial and error*/
float xRotation = 0, yRotation = 0, zRotation = 0;

/* The 6 direction vectors */
PVector3f forward(0,0,-1);
PVector3f back = -forward;
PVector3f up(0,1,0);
PVector3f down = -up;
PVector3f left = up * forward;
PVector3f right = -left;

/* Camera Vector for translations */
PVector3f cam(0.0f, 0.0f, 15.0f);

const float cameraSpeed = 0.75f;
const float shapeSpeed = 0.5f;

/* Moves camera positions along a vector*/
void moveCamera(PVector3f dirVector, float amt)
{
	cam = cam + (dirVector*amt);
}

/*CAMERA CONTROL AND SHAPE CONTROL*/
	/*WASD+Space+z to control the camera*/
void keyboard(unsigned char key, int x, int y)
{
	/*Esc to exit the program*/
	if(key == 27)
	{
		exit(0);
	}

	
	else if (key == 'w')
	{
		moveCamera(forward, cameraSpeed);
	} else if (key == 'a')
	{
		moveCamera(left, cameraSpeed);
	} else if (key == 's')
	{
		moveCamera(back, cameraSpeed);
	} else if (key == 'd')
	{
		moveCamera(right, cameraSpeed);
		/* Space bar */
	}  else if (key == 32)
	{
		moveCamera(lp, cameraSpeed);
	} else if (key == 'c')
	{
		moveCamera(down, cameraSpeed);
	}
}

/*
	Track the motion of the mouse in the screen to 
	rotate around the z and y axes
*/
void mouseMotion(int x, int y)
{
	/* Make mouse invisible */
	glutSetCursor(GLUT_CURSOR_NONE);
	/* Calculate center of screen */
	int midX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int midY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	/* Increase rotation by distance moved from center*/
	yRotation +=  mouseSensitivity * (midX - x);
	xRotation += mouseSensitivity * (midY - y);

	if (stall > 5)
	{
		/* Move pointer back to center after 5 'counts'*/
		glutWarpPointer(midX, midY); 
		stall = 0;
	}
	stall++;
}

void display()
{
	/*6 DOF camera controls*/
	/* Negative because technically we are moving world*/
	glTranslatef(-cam.x,-cam.y,-cam.z);
	
	glRotatef(-xRotation,1,0,0);
	glRotatef(-yRotation,0,1,0);
	glRotatef(-zRotation,0,0,1);

	/* ... */
}