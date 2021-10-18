#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game2.h"
#include <ctime>

using namespace std;

Game2::Game2(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{
	m_nbParticules = 3;
	m_blob = vector<Particule*>(); 
}

void Game2::doKeyboard(unsigned char key, int x, int y) {

	switch (key) {
	// a faire plus tard
	case 27:// echap
		exit(EXIT_SUCCESS);
		break;
	case 'q':
		
		break;
	case's':
	case'z':
	case'd':
	case 32: //sapce bar
	default:
		break;
	}
}

void Game2::createBlob(){
	//equivalent du lauch particule de game1
	Particule p;
	ParticleGravity* pg =  new ParticleGravity();
		for (int i = 0; i < m_nbParticules; i++) {
		// on créée les particules avec leurs attribus
		double masse = 50000;
		Vecteur3D velocity;
		Vecteur3D position;
		double damping = 0.9;
		Particule* p =  new Particule(masse, position, velocity, damping);
		m_blob.push_back(p);
			//On initialise la position des particules du blob
		if (i == 0) //triangle
			m_blob[i]->setPosition(Vecteur3D(0.0, 0.0, 0.0));
		else if (i == 1)
			m_blob[i]->setPosition(Vecteur3D(1.0, 0.0, 0.0));
		else
			m_blob[i]->setPosition(Vecteur3D(0.5, 0.75, 0.0));
			// on créée la/les forces en passant la particule concernée en paramètre
			// on ajoute tout cela au registry
		//m_registry.add(m_blob[i], pg);
		for (int j=0; j < m_blob.size();j++){
			for(int k=0;k<m_blob.size();k++){
				if(j!=k){
					ParticleSpring* ps = new ParticleSpring(m_blob[k], 2000.0, 0.8);
					m_registry.add(m_blob[j], ps);
				}
			}
		}
	}
}

void Game2::drawParticule(Particule* particule) {
	Vecteur3D position;
	position = particule->getPosition();
	glColor3f(1, 1, 0); //yellow
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
	
}

void Game2::doUpdatePhysics() {

	double deltaTime = updateTime();
	m_registry.UpdateForce(deltaTime); //met à joue la valeur de chaque force sur les particules

	for (int i = 0; i < m_nbParticules; i++) {
		//calculates with respect to the position and speed of the previous frame 
		m_blob[i]->integrate(deltaTime);  //loi de Newton et mise à jour des positions et vitesses
	}
	glutPostRedisplay();
}

void Game2::doDisplay() {

	//cout << m_blob[0]->getPosition();
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X,0.5,Z, X,0.5,0, 0.0, 1.0, 0.0); //a changer avec position particule
	

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 

	//Draw ground
	glColor3f(0.1, 0.0, 0.0); //brown
	glBegin(GL_QUADS);
	glVertex3f(-10, 0.0, -10);
	glVertex3f(-10, 0.0, 10);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, -10);
	glEnd();
	//Draw water
	glColor3f(0.5, 1.0, 1.0); //cyan 
	glBegin(GL_QUADS);
	glVertex3f(0.0, -1, -10.0);
	glVertex3f(0.0, -1, -10.0);
	glVertex3f(10,-1, -10.0);
	glVertex3f(0.0, -1, 10);
	glEnd();

	//for the first particle (the one we can control)
	Vecteur3D position = m_blob[0]->getPosition();
	glColor3f(1, 0, 0); //red
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	// draw each particle contain in the particle board
	for (int i = 1; i < m_nbParticules; i++) {
		drawParticule(m_blob[i]); 
			
	}
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();

	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
}



int Game2::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Blob game");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	//creating blob
	createBlob();

	glutMainLoop();
	return EXIT_SUCCESS;

}