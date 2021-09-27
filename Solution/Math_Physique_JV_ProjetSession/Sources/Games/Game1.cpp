#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game1.h"
#include <ctime>

#define ProjectileMax 7
using namespace std;
int projectileChosen = 0; //type of projectile chosen
int shape = 0;// 0 -> Sphere, 1-> Cube, 2->Torus, 3-> Teapot,4->ellipse 3D

Game1::Game1(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{
	partTabl = vector<Particule>();
}

void Game1::keyboard2(unsigned char key, int x, int y) {

	switch (key) {

	case 97 : // 'a' key
		projectileChosen = (projectileChosen + 1) % ProjectileMax;
		break;
	case 32: //space bar
		launchParticule();
		break;
	case 27: //escape
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

//Draw the particle 
void Game1::drawParticule(Particule particule) { //gamebase et spécifier dans game1
	Vecteur3D position;
	position = particule.getPosition();

	glColor3f(particule.getRVBColor().getX(), particule.getRVBColor().getY(), particule.getRVBColor().getZ());
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	//choose the shape of your particle 
	switch (shape) {
	case 0:
		//a sphere
		//parameters: radius,slices (number of disvisions aroud z), stacks ( number of divisions along z)
		glutSolidSphere(particule.getFormSize().getX(), particule.getFormSize().getY(), particule.getFormSize().getZ()); 
		break;
	case 1:
		//a cube
		//parameters: size
		glutSolidCube(particule.getFormSize().getX()); 
		break;
	case 2:
		//a torus
		glRotatef(45.0, 1.0, 0.0, 0.0);
		//parameters: Inner radius of the torus, Outer radius of the torus, Number of sides for each radial section, 
		//Number of radial divisions for the torus
		glutSolidTorus(particule.getFormSize().getX(), particule.getFormSize().getY(), particule.getFormSize().getZ(), 100); 
		break;
	case 3:
		//a teapot
		//parameters: size
		glutSolidTeapot(particule.getFormSize().getX()); 
		break;
	default:
		break;
	}
	glPopMatrix();

	//we don't want to store more than 20 particles
	if(partTabl.size() > 20){
		partTabl.erase(partTabl.begin());
		cout << partTabl.size();
	}
}

//Create a Particle
void Game1::launchParticule() {
	Particule p;
	switch (projectileChosen) {
		case 0:
			//Tennis ball: weight 58g , diameter 6cm, color yellow
			p = Particule(0.058, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 5, 10), 1, Vecteur3D(1.0, 1.0, 0), Vecteur3D(0.03, 100, 100));
			shape = 0;
			partTabl.push_back(p);
			break;

		case 1:
			//Basket ball: weight 600g, diameter 24cm, color orange 
			p = Particule(0.6, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 5, 4), 1, Vecteur3D(1.0, 0.5, 0), Vecteur3D(0.12, 100, 100));
			shape = 0;
			partTabl.push_back(p);
			break;
		case 2:
			//Bowling ball: weight 7kg, diameter 21cm, color red
			p = Particule(7, Vecteur3D(X, 1.5, Z), Vecteur3D(0, 0, 10), 1, Vecteur3D(1.0, 0, 0), Vecteur3D(0.10, 100, 100));
			partTabl.push_back(p);
			shape = 0;
			break;
		case 3:
			//Golf ball: weight 45g, diameter 4,27, color white
			p = Particule(0.045, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 10, 10), 1, Vecteur3D(1, 1, 1), Vecteur3D(0.0227, 30, 30));
			partTabl.push_back(p);
			shape = 0;
			break;
		case 4:
			//Box: weight 10kg, size 30 cm, color brown 
			p = Particule(10, Vecteur3D(X, 1, Z), Vecteur3D(0, 2, 5), 1, Vecteur3D(0.1, 0, 0), Vecteur3D(0.3, 0, 0));
			partTabl.push_back(p);
			shape = 1;
			break;
		case 5:
			//Donuts: weight 50g, dimaeter 7cm,  color pink
			p = Particule(0.05, Vecteur3D(X, 1, Z), Vecteur3D(0, 0, 15), 1, Vecteur3D(2.0, 0.5, 1), Vecteur3D(0.03, 0.06, 100));
			partTabl.push_back(p);
			shape = 2;
			break;
		case 6:
			//Teapot: weight 594g, size 20cm, color purple
			p = Particule(0.594, Vecteur3D(X, 0.75, Z), Vecteur3D(0, 5, 5), 1, Vecteur3D(0.5, 0.5, 0.5), Vecteur3D(0.20, 0, 0));
			partTabl.push_back(p);
			shape = 3;
			break;
		default:
			p = Particule(200, Vecteur3D(X, 1.5, Z), Vecteur3D(0, 0, 10), 1, Vecteur3D(0, 0, 0), Vecteur3D(0.5, 100, 100));
			partTabl.push_back(p);
			shape = 0;
			break;
	}
}

//updates the position, acceleration and speed of 
//each particle in the game in each frame time
void Game1::updatePhysics2() {

	double deltaTime = updateTime();

	for (int i = 0; i < partTabl.size(); i++) {
		//calculates with respect to the position and speed of the previous frame 
		partTabl[i].integrate(deltaTime); 
	}

	glutPostRedisplay();
}

//overload of the glut method "glutDisplayFunc. 
//Is executed at each frame
void Game1::display2() {
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X, 1.0, Z, X + camX, 1.0, Z + camZ, 0.0, 1.0, 0.0); 

	// rotate of beta along the axes X
	glRotatef(beta, 1, 0, 0);

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 


	for (int i = 0; i < partTabl.size();i++) {
		// draw each particle contain in the particle board
		drawParticule(partTabl[i]); 
	}
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();
	
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
	
}



int Game1::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Launching some projectiles");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}
