
#pragma comment (lib, "Winmm.lib")
#include <iostream>

#include <windows.h>
#include <gl/glut.h>
#include "Sources/Math/Vecteur3D.h"
#include "Sources/Physic/Particule.h"

#define ProjectileMax 5
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

int projectileChosen = 0;
vector<Particule> partTabl;
string shape = "sphere";
//Particule TableauParticule[20];


void drawParticule(Particule particule) {
	Vecteur3D position;
	position = particule.getPosition();

	glColor3f(particule.getRVBColor().getX(), particule.getRVBColor().getY(), particule.getRVBColor().getZ());
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	switch (shape) {
	case "sphere":
		glutSolidSphere(particule.getSphereSize().getX(), particule.getSphereSize().getY(), particule.getSphereSize().getZ()); // radius,slices (number of disvisions aroud z), stacks ( number of divisions along z)
		break;
	default:
		break;
	}
	glPopMatrix();
}




void launchParticule() {
	Particule p;
	switch (projectileChosen) {
		case 0:
			//balle de tennis poids 58g , diamètre 6cm, couleur jaune
			p = Particule(0.058, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 5, 10), 1, Vecteur3D(1.0, 1.0, 0), Vecteur3D(0.03, 100, 100));
			shape = 0;
			partTabl.push_back(p);
			break;

		case 1:
			//balle de basket poids 600g, diamétre 24cm, couleur orange 
			p = Particule(0.6, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 5, 4), 1, Vecteur3D(1.0, 0.5, 0), Vecteur3D(0.12, 100, 100));
			shape = 0;
			partTabl.push_back(p);
			break;
		case 2:
			//boule de bowling poids 7kg, diamétre 21cm, couleur rouge
			p = Particule(7, Vecteur3D(X, 1.5, Z), Vecteur3D(0, 0, 10), 1, Vecteur3D(1.0, 0, 0), Vecteur3D(0.10, 100, 100));
			partTabl.push_back(p);
			break;
		case 3:
			//balle de golf poids 45g, diamétre 4,27 , couleur blanc
			p = Particule(0.045, Vecteur3D(X, 1.5, Z), Vecteur3D(0, 5, 10), 1, Vecteur3D(1, 1, 1), Vecteur3D(0.0227, 30, 30));
			partTabl.push_back(p);
			break;
		default:
			p = Particule(200, Vecteur3D(X, 1.5, Z), Vecteur3D(0, 0, 10), 1, Vecteur3D(0, 0, 0), Vecteur3D(0.5, 100, 100));
			partTabl.push_back(p);
			break;
	}

}




void updatePhysics() {

	static double current_time = 0;
	static double last_time = 0;

	last_time = current_time;
	current_time = glutGet(GLUT_ELAPSED_TIME);
	double deltaTime = (current_time - last_time) * 0.001;

	for (int i = 0; i < partTabl.size(); i++) {
		partTabl[i].integrate(deltaTime);
	}

	glutPostRedisplay();

}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(X, 1.0f, Z, X + camX, 1.0f, Z + camZ, 0.0f, 1.0f, 0.0f);
	glRotatef(beta, 1, 0, 0);

	for (int i = 0; i < partTabl.size();i++) {
		drawParticule(partTabl[i]);
	}

	glutSwapBuffers();

	glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(updatePhysics);

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
		angle += (2 / ANG_SPEED) * (0.01f);
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle -= (2 / ANG_SPEED) * 0.01f;
		camX = sin(angle);
		camZ = -cos(angle);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 97 : // touche a
		projectileChosen = (projectileChosen + 1) % ProjectileMax;
		break;
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

void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0, width * 1.0 / height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow(argv[0]);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;
}