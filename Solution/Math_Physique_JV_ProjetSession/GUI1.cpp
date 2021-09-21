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

// Global variables  
//cam position
double X = 0.0;
double Z = -5.0;

//cam direction
double alpha = 0; // camera along y axis
double beta = 0; //camera along z axis

struct Object {
	Particule particule;

	void DrawParticule()
	{
		Vecteur3D position;
		position = particule.getPosition();

		glColor3f(1, 1, 1); // black 
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), position.getZ()); // put the object at his position
		glutSolidSphere(0.3, 10, 10); // object is a sphere 
		glPopMatrix();

	}
};

Object tableauObjet[20];

void DrawPlan()
{

	glColor3f(0, 1, 0);//green
	glBegin(GL_QUADS); // set the plan 
	glVertex3f(-100.0, 0.0, -100.0); 
	glVertex3f(-100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, -100.0);
	glEnd();

}


void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(X, 1.0, Z, X  , 1.0, Z + 1, 0.0, 1.0, 0.0);	//Place the camera
	glRotatef(beta, 1, 0, 0);          // rotate around x
	glRotatef(alpha, 0, 1, 0);          // rotate around Z

	DrawPlan(); 
	for (Object* objet = tableauObjet; objet < tableauObjet + 20; objet++) {

		objet->DrawParticule();
	}
	glutSwapBuffers();

	//glEnable(GL_DEPTH_TEST);
	double deltaTime = updateTime(lastTime);
	updateInput();
	updatePhysics(deltaTime);
	updateOutput();
}

double updateTime(double lastTime) {
	//UPDATE le temps 
	
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME); //getTime();
	double detaTime = (currentTime - lastTime);
	return detaTime;
}

void updateInput() {
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);
}

void updatePhysics(double deltaTime) {
	//appeler la méthode integrate de la particule qui met à jour les vecteurs
	for (Object* objet = tableauObjet; objet < tableauObjet + 20; objet++) {
		objet->particule.integrate(deltaTime);
	}
}

void updateOutput() {
//dessiner la particule sous sa nouvelle position
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'esc':
	case 27:
		exit(0);
		break;
	case 'a':
		Object* objet;
		objet = new Object();
		objet->particule.setMasse(20.0);
		objet->particule.setAcceleration(0, -2, 0);
		objet->particule.setVelocity(0, 0, 20);
		objet->particule.setPosition(X, 0.75, Z);
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void arrows(int key, int x, int y)
{
	
	switch (key)
	{
	case GLUT_KEY_LEFT:
		alpha = alpha + ANG_SPEED;
		break;
	case GLUT_KEY_RIGHT:
		alpha = alpha - ANG_SPEED;
		break;
	case GLUT_KEY_UP:
		beta = beta + ANG_SPEED;
		break;
	case GLUT_KEY_DOWN:
		beta = beta - ANG_SPEED;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	if (width < height)
		glViewport(0, (height - width) / 2, width, width);
	else
		glViewport((width - height) / 2, 0, height, height);
}

int launch(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(X, 1.0, Z, X, 1.0, Z + 1, 0.0, 1.0, 0.0);	//Place the camera
	glRotatef(beta, 1, 0, 0);          // rotate around x
	glRotatef(alpha, 0, 1, 0);          // rotate around Z

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	

	// define the projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	// define the viewing transformation
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
	return EXIT_SUCCESS;
	
}