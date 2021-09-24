#include <iostream>
#include <windows.h>
#include <gl/glut.h>
#include "../Math_Physique_JV_ProjetSession/Sources/Math/Vecteur3D.h"
#include "../Math_Physique_JV_ProjetSession/Sources/Physic/Particule.h"
#include <ctime>

using namespace std;

static double currentTime = 0;
static double lastTime = 0;



#define SPEED 0.1 //OpenGL unit
#define ANG_SPEED 0.5 //degrees
using namespace std;


// Global variables  
//cam position
double X = 0.0;
double Z = 5.0;


//cam direction
double beta = 0; //camera along z axis
double angle = 3.14;
// actual vector representing the camera's direction
double camX = 0.0, camZ = 1.0;



struct Object {
	Particule particule;

	void DrawParticule()
	{
		Vecteur3D position;
		position = particule.getPosition();

		glColor3f(0, 0, 0); // black 
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), position.getZ()); // put the object at his position
		glutSolidSphere(0.3, 10, 10); // object is a sphere 
		glPopMatrix();

	}
};

Object tableauObject[20];


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(X, 1.0f, Z, X + camX, 1.0f, Z + camZ, 0.0f, 1.0f, 0.0f);
	glRotatef(beta, 1, 0, 0);

	for (Object* object = tableauObject; object < tableauObject + 20; object++) {
		object->DrawParticule();
		
	}

	glutSwapBuffers();

	glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

}

double updateTime(double lastTime) {
	//UPDATE le temps 
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME); //getTime();
	double detaTime = (currentTime - lastTime);
	return detaTime;
}



void updatePhysics() {
	float duration = (float)30 * 0.001;
	if (duration <= 0.0f) return;

	for (Object* object = tableauObject; object < tableauObject + 20; object++) {
			object->particule.integrate(duration);
	}
	glutPostRedisplay();
}

void updateOutput() {
//dessiner la particule sous sa nouvelle position
}



void launchParticule() {

	Object* object;
	
	object->particule.setMasse(10);
	object->particule.setPosition(X, 0.75, Z);
	object->particule.setVelocity(0, 0, 50);
	object->particule.setAcceleration(0, -2, 0);
	object->particule.setDamping(1);
	

}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 32: //  barre espace
		launchParticule();
		break;
	case 'esc':
	case 27: 
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

void arrows(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP:
		beta += ANG_SPEED;
		break;
	case GLUT_KEY_DOWN:
		beta -= ANG_SPEED;
		break;
	case GLUT_KEY_LEFT:
		angle -= (2 / ANG_SPEED) * (0.01f);
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += (2 / ANG_SPEED) * 0.01f;
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	default:
		break;
	}
}

void updateInput() {
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);
}

void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0, width * 1.0 / height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int launchGame(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow(argv[0]);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(updateInput);
	glutIdleFunc(updatePhysics);

	glutMainLoop();
	return EXIT_SUCCESS;
	
}