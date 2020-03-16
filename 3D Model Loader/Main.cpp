//  
// Example code for OpenGL programming
//
#define GLEW_STATIC
#include "GL/glew.h"
#include "meshLoader.h"
#include "skyboxLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <ctime>
#include <SOIL/SOIL.h>

int nFPS = 30;
float fRotateAngle = 0.f;
clock_t startClock=0,curClock;
long long int prevF=0,curF=0;
int dipMode=1;
meshLoader m;
skyboxLoader s;

void init(void)
{
	//Load our teapot file and textures
	m.parseFile("teapot_0.obj");
	s.loadTextures();
	m.loadTexture();

	//set clear color to dark blue
	glClearColor(0.1, 0.1, 0.2, 1.0);

	/*
	Lighting Stuff Begins here
	*/

	//Set Materials
	GLfloat amb[] = { 0.2, 0.2, 0.2 };
	GLfloat diff[] = { 1.0, 1.0, 1.0 };
	GLfloat spec[] = { 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_BACK, GL_SHININESS, mat_shininess);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BACK);

}

void display(void)
{
	//Set light to a shade of blue
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.4, 0.6, 0.8, 1.0 };
	GLfloat light_specular[] = { 0.6, 0.8, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 10.0, 10.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	curF++;
	// put your OpenGL display commands here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset OpenGL transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // reset transformation matrix to identity

	gluLookAt(0.0f, 4.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0, 1.0, 0.0);

	//Disable Lighting so only teapot is affected by it
	glDisable(GL_LIGHTING);
	s.draw();
	glEnable(GL_LIGHTING);

	//Rotate ONLY the teapot
	glPushMatrix();
	glRotatef(fRotateAngle, 0.f, 1.f, 0.f);
	m.draw();
	glPopMatrix();

	glutSwapBuffers();	// swap front/back framebuffer to avoid flickering 
	curClock = clock();
	float elapsed = (curClock - startClock) / (float)CLOCKS_PER_SEC;
	if (elapsed>1.0f){
		float fps = (float)(curF - prevF) / elapsed;
		printf("fps:%f\n", fps);
		prevF = curF;
		startClock = curClock;
	}

}
 
void reshape (int w, int h)
{
	// reset viewport ( drawing screen ) size
	glViewport(0, 0, w, h);
	float fAspect = ((float)w)/h; 
	// reset OpenGL projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f,fAspect,0.001f,100.f); 
}


void timer(int v)
{
	fRotateAngle += 1.f; // change rotation angles
	glutPostRedisplay(); // trigger display function by sending redraw into message queue
	glutTimerFunc(1000/nFPS,timer,v); // restart timer again
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	//glewInit();
	// set up for double-buffering & RGB color buffer & depth test
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow((const char*)"Teapot Simulator 2014");

	init(); // setting up user data & OpenGL environment

	// set up the call-back functions 
	glutDisplayFunc(display);  // called when drawing 
	glutReshapeFunc(reshape);  // called when change window size
	glutTimerFunc(100, timer, nFPS); // a periodic timer. Usually used for updating animation

	startClock = clock();

	glutMainLoop(); // start the main message-callback loop

	return 0;
}

