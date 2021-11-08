#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game2.h"
#include <ctime>

using namespace std;

Game2::Game2(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{	
	m_contactRegistry = ParticleContactRegistry();
	m_forceRegistry = ParticleForceRegistry();
	m_groundHeight = 1.5;
	m_waterHeight = 1;
	m_k = 20;
	m_l0 = 0.3;
	Y = 1;
	Z = 5;
	m_nbParticules = 5;
	m_cables = vector<ParticleCable*>();
	m_blob = vector<Particule*>(); 
	particuleSize = 0.07;
	m_particuleRestitution = 0.5;
}

void Game2::doArrows(int key, int xx, int yy){
	InputForce* force = m_forceRegistry.getInputForce();
	double coeff = 50;
 
	switch (key) {
	
	case GLUT_KEY_LEFT:
		force->changeForceValue(-coeff, 0.0, 0.0);
		break;
	case GLUT_KEY_DOWN:
		force->changeForceValue(0.0, -coeff * 4, 0.0);
		break;
	case GLUT_KEY_UP:
		force->changeForceValue(0.0, coeff, 0.0);
		break;
	case GLUT_KEY_RIGHT:
		force->changeForceValue(coeff, 0.0, 0.0);
		break;
	default:
		break;
	}
	
	cout << force->getForce() << endl;
}

void Game2::doKeyboard(unsigned char key, int x, int y) {
	InputForce* force = m_forceRegistry.getInputForce();
	double coeff = 50;
	
	switch (key) {
	case 27:// echap
		exit(EXIT_SUCCESS);
		break;
	case 'a': 
		force->changeForceValue(-coeff, 0.0, 0.0);
		break;
	case 's':
		force->changeForceValue(0.0, -4*coeff, 0.0);
		break;
	case 'w':
		force->changeForceValue(0.0, coeff, 0.0);
		break;
	case 'd':
		force->changeForceValue(coeff, 0.0, 0.0);
		break;
	default:
		break;
	}
	cout << force->getForce() << endl;
}

void Game2::createBlob(){
	//initialization of the blob
	Particule p;
	for (int i = 0; i < m_nbParticules; i++) {
		// we create each particle with its attributes
		double masse = 1;
		Vecteur3D velocity = Vecteur3D();
		Vecteur3D position;
		double damping = 0.8;
		Particule* p =  new Particule(masse, position, velocity, damping);
		m_blob.push_back(p);
		//we initialize each pearticle's position
		if (i == 0) 
			m_blob[i]->setPosition(Vecteur3D(-2.2, m_groundHeight + particuleSize, 0.0));
		else if (i == 1)
			m_blob[i]->setPosition(Vecteur3D(-2, m_groundHeight + particuleSize, 0.0));
		else if (i == 2)
			m_blob[i]->setPosition(Vecteur3D(-1.8, m_groundHeight + particuleSize, 0.0));
		else if (i == 3)
			m_blob[i]->setPosition(Vecteur3D(-2.1, m_groundHeight + 2 * particuleSize, 0.0));
		else if (i == 4)
			m_blob[i]->setPosition(Vecteur3D(-1.9, m_groundHeight + 2 * particuleSize, 0.0));
	}

	//every particle has gravity
	for (int i = 0; i < m_nbParticules; i++)
	{
		m_forceRegistry.add(m_blob[i], new ParticleGravity());
	}

	//particles are bound to each other with springs
	for (int j = 0; j < m_blob.size(); j++) {
		for (int k = 0; k < m_blob.size(); k++) {
			if (j != k) {
				m_forceRegistry.add(m_blob[j], new ParticleSpring(m_blob[k], m_k, m_l0));
			}
		}
	}

	//we create a list of cable between each particle
	for (int i = 0; i < m_nbParticules; i++) {
		for (int k = i + 1; k < m_nbParticules; k++) {
			ParticleCable* particuleCable = new ParticleCable(m_blob[i], m_blob[k], m_l0 * 5);
			m_cables.push_back(particuleCable);
		}
	}
	
	//we create a buoyancy force for each particle
	for (int i = 0; i < m_nbParticules; i++)
	{
		m_forceRegistry.add(m_blob[i], new ParticleBuoyancy(particuleSize, 4.f / 3.f * 3.14 * std::pow(particuleSize, 3), m_waterHeight, 1000));
	}

	//we add the inputForce
	m_forceRegistry.add(m_blob[0], new InputForce(Vecteur3D()));
}

void Game2::drawParticule(Particule* particule) {
	Vecteur3D position;
	position = particule->getPosition();
	glColor3f(1, 1, 0); //yellow
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glutSolidSphere(particuleSize, 10, 10);
	glPopMatrix();
	
}

void Game2::doUpdatePhysics() {
	double deltaTime = updateTime();

	cout << m_blob[0]->getPosition() << endl;

	m_forceRegistry.UpdateForce(deltaTime); //update each force 

	for (int i = 0; i < m_nbParticules; i++) {
		m_blob[i]->integrate(deltaTime);
	}
	
	m_contactRegistry.updateContact(m_blob, m_cables, particuleSize, m_particuleRestitution, m_groundHeight, m_waterHeight);

	m_resolver.resolveContacts(m_contactRegistry.getContactList());

	m_contactRegistry.clear();

	//clean Input force
	InputForce* force = m_forceRegistry.getInputForce();
	force->changeForceValue(0, 0.0, 0.0);

	glutPostRedisplay();
}

void Game2::doDisplay() {

	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X,Y,Z, 0,Y,0, 0.0, 1.0, 0.0); //a changer avec position particule
	

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 

	//Draw ground
	glColor3f(0.1, 0.0, 0.0); //brown
	glBegin(GL_QUADS);
	glVertex3f(-100, m_groundHeight, 0);
	glVertex3f(-100, -150, 0.0);
	glVertex3f(0.0, -150, 0.0);
	glVertex3f(0.0, m_groundHeight, 0.0);
	glEnd();
	//Draw water
	glColor3f(0.5, 1.0, 1.0); //cyan 
	glBegin(GL_QUADS);
	glVertex3f(0, m_waterHeight, 0);
	glVertex3f(0, -150, 0.0);
	glVertex3f(100, -150, 0.0);
	glVertex3f(100, m_waterHeight, 0.0);
	glEnd();

	//for the first particle (the one we can control)
	Vecteur3D position = m_blob[0]->getPosition();
	glColor3f(1, 0, 0); //red
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glutSolidSphere(particuleSize, 10, 10);
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