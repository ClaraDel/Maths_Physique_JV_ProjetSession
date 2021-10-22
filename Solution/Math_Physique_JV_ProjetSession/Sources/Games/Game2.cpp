#include <iostream>
#include <windows.h>
#include<GL/glut.h>
#include <string>
#include "Game2.h"
#include <ctime>


using namespace std;

Game2::Game2(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{	
	m_groundHeight = 1.5;
	m_waterHeight = 1;
	m_k = 2;
	l0 = 0.3;
	Z = 10;
	m_nbParticules = 3;
	m_blob = vector<Particule*>(); 
	particuleSize = 0.1 ;
	particuleRestitution = 0.6;
	particuleContactList = vector<ParticleContact*>();
}

void Game2::doKeyboard(unsigned char key, int x, int y) {
	ConstantForce* force = new ConstantForce();
	double coeff = 50;
	
	switch (key) {
	case 27:// echap
		exit(EXIT_SUCCESS);
		break;
	case 'q': 
		force = new ConstantForce(Vecteur3D(-coeff, 0.0, 0.0));
		break;
	case 's':
		force = new ConstantForce(Vecteur3D(0.0, -coeff, 0.0));
		break;
	case 'z':
		force = new ConstantForce(Vecteur3D(0.0, coeff, 0.0));
		break;
	case 'd':
		force = new ConstantForce(Vecteur3D(coeff, 0.0, 0.0));
		break;
	case 32: //sapce bar
	default:
		break;
	}
	//m_blob[0]->addForce(force);
	m_registry.add(m_blob[0], force);
}

void Game2::createBlob(){
	//equivalent du lauch particule de game1
	Particule p;
		for (int i = 0; i < m_nbParticules; i++) {
		// on créée les particules avec leurs attribus
		double masse = 3.5;
		Vecteur3D velocity;
		Vecteur3D position;
		double damping = 0.9;
		Particule* p =  new Particule(masse, position, velocity, damping);
		m_blob.push_back(p);
			//On initialise la position des particules du blob
		if (i == 0) //triangle
			m_blob[i]->setPosition(Vecteur3D(-4.5, 5, 0.0));
		else if (i == 1)
			m_blob[i]->setPosition(Vecteur3D(-4, 5, 0.0));
		else
			m_blob[i]->setPosition(Vecteur3D(-4.5, 5.5, 0.0));
	}
}

void Game2::checkParticleCollisions() {
	//for each particle, we check if they ar in collision with the ground
	for (int i = 0; i < m_blob.size(); i++) {
		for (int j = i + 1; j < m_blob.size(); j++) {
			Vecteur3D distanceVect = m_blob[i]->getPosition() - m_blob[j]->getPosition();
			double distanceVal = distanceVect.norm();
			if (distanceVal <= 2*particuleSize) {
				double penetration = 2*particuleSize - distanceVal ;
				Vecteur3D contactNormal = distanceVect.normalization();
				ParticleContact* particleContact = new ParticleContact(m_blob[i],m_blob[j], particuleRestitution, penetration, contactNormal);
				particuleContactList.push_back(particleContact);
			}
		}
	}
}

void Game2::checkWaterInteractions() {
	//for each particle, we check if its under water
	for (int i = 0; i < m_nbParticules; i++) {
		if (m_blob[i]->getPosition().getY() <= m_waterHeight + particuleSize && m_blob[i]->getPosition().getX() >= 0 && m_blob[i]->getPosition().getX() <= 100){
			double volume = 4.f / 3.f * 3.14 * std::pow(particuleSize, 3);
			ParticleBuoyancy* buoyancy = new ParticleBuoyancy(particuleSize, volume, m_waterHeight, 1000);
			m_registry.add(m_blob[i], buoyancy);
		}
	}
}

void Game2::checkGroundCollisions(){
	for (int i = 0; i < m_nbParticules; i++) {
		float radius = particuleSize;
		float distance = m_blob[i]->getPosition().getY()-m_groundHeight;

		// check if the particule is above or under ground 
		if(std::abs(distance) <= radius && m_blob[i]->getPosition().getX() < 0 && m_blob[i]->getPosition().getX() >= -100)
			{
				float penetration = radius - distance;
				Vecteur3D normal= Vecteur3D(0.0, 1.0, 0.0);
	            ParticleContact* particleContact = new ParticleContact(m_blob[i],NULL,0.5,penetration,normal);
				particuleContactList.push_back(particleContact);	
			}
	}
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
	particuleContactList = vector<ParticleContact*>();
	//on met à jour quelle particule a quelle force

	//toutes les particules ont la gravité
	for (int i = 0; i < m_nbParticules; i++)
	{
		m_registry.add(m_blob[i], new ParticleGravity());
	}

	//les ressorts les uns avec les autres
	for (int j = 0; j < m_blob.size(); j++) {
		for (int k = 0; k < m_blob.size(); k++) {
			if (j != k) {
				m_registry.add(m_blob[j], new ParticleSpring(m_blob[k], m_k, l0));
			}
		}
	}

	//cout << m_blob[0]->getPosition();
	checkWaterInteractions();
	
	m_registry.UpdateForce(deltaTime); //update each force 

	for (int i = 0; i < m_nbParticules; i++) {
		m_blob[i]->integrate(deltaTime);
	}
	
	checkParticleCollisions();
	checkGroundCollisions();

	//cout << particuleContactList.size()<<endl;
	m_resolver.resolveContacts(particuleContactList);

	m_registry.clear();

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
	gluLookAt(X,0.5,Z, 0,0.5,0, 0.0, 1.0, 0.0); //a changer avec position particule
	

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