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
	m_k = 20;
	m_l0 = 0.3;
	Y = 1;
	Z = 5;
	m_nbParticules = 5;
	m_cables = vector<ParticleCable*>();
	m_blob = vector<Particule*>(); 
	particuleSize = 0.07;
	m_particuleRestitution = 0.5;
	m_contactRegistry = vector<ParticleContact*>();
}


void Game2::doArrows(int key, int xx, int yy){
	ConstantForce* force = new ConstantForce();
	double coeff = 50;
 
	switch (key) {
	
	case GLUT_KEY_LEFT:
		force = new ConstantForce(Vecteur3D(-coeff, 0.0, 0.0));
		break;
	case GLUT_KEY_DOWN:
		force = new ConstantForce(Vecteur3D(0.0, -coeff * 4, 0.0));
		break;
	case GLUT_KEY_UP:
		force = new ConstantForce(Vecteur3D(0.0, coeff, 0.0));
		break;
	case GLUT_KEY_RIGHT:
		force = new ConstantForce(Vecteur3D(coeff, 0.0, 0.0));
		break;
	default:
		break;
	}
	m_forceRegistry.add(m_blob[0], force);
}


void Game2::doKeyboard(unsigned char key, int x, int y) {
	ConstantForce* force = new ConstantForce();
	double coeff = 50;
	
	switch (key) {
	case 27:// echap
		exit(EXIT_SUCCESS);
		break;
	case 'a': 
		force = new ConstantForce(Vecteur3D(-coeff, 0.0, 0.0));
		break;
	case 's':
		force = new ConstantForce(Vecteur3D(0.0, -coeff*4, 0.0));
		break;
	case 'w':
		force = new ConstantForce(Vecteur3D(0.0, coeff, 0.0));
		break;
	case 'd':
		force = new ConstantForce(Vecteur3D(coeff, 0.0, 0.0));
		break;
	default:
		break;
	}
	m_forceRegistry.add(m_blob[0], force);
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
	//we create a list of cable between each particle
	for (int i = 0; i < m_nbParticules; i++) {
		for (int k = i + 1; k < m_nbParticules; k++) {
			ParticleCable* particuleCable = new ParticleCable(m_blob[i], m_blob[k], m_l0 * 5);
			m_cables.push_back(particuleCable);
		}
	}
}

void Game2::checkParticleCollisions() { // DANS CONTACT GENERATOR
	//for each particle, we check if it has collision with another particle
	for (int i = 0; i < m_blob.size(); i++) {
		for (int j = i + 1; j < m_blob.size(); j++) {
			Vecteur3D distanceVect = m_blob[i]->getPosition() - m_blob[j]->getPosition();
			double distanceVal = distanceVect.norm();
			if (distanceVal <= 2 * particuleSize) {
				double penetration = 2 * particuleSize - distanceVal ;
				Vecteur3D contactNormal = distanceVect.normalization();
				ParticleContact* particleContact = new ParticleContact(m_blob[i],m_blob[j], m_particuleRestitution, penetration, contactNormal);
				m_contactRegistry.push_back(particleContact);
			}
		}
	}
}

void Game2::checkWaterInteractions() { // DANS CONTACT GENERATOR
	//for each particle, we check if its under water
	for (int i = 0; i < m_nbParticules; i++) {
		if (m_blob[i]->getPosition().getY() <= m_waterHeight + particuleSize && m_blob[i]->getPosition().getX() >= 0 && m_blob[i]->getPosition().getX() <= 100){
			double volume = 4.f / 3.f * 3.14 * std::pow(particuleSize, 3);
			ParticleBuoyancy* buoyancy = new ParticleBuoyancy(particuleSize, volume, m_waterHeight, 1000);
			m_forceRegistry.add(m_blob[i], buoyancy);
		}
	}
}

void Game2::checkGroundCollisions(){ // DANS CONTACT GENERATOR
	for (int i = 0; i < m_nbParticules; i++) {
		float radius = particuleSize;
		float distance = m_blob[i]->getPosition().getY()-m_groundHeight;

		// check if the particule is above or under ground 
		if(distance <= radius && m_blob[i]->getPosition().getX() < 0 && m_blob[i]->getPosition().getX() >= -100)
			{
				float penetration = radius - distance;
				Vecteur3D normal= Vecteur3D(0.0, 1.0, 0.0);
	            ParticleContact* particleContact = new ParticleContact(m_blob[i],NULL,0.5,penetration,normal);
				m_contactRegistry.push_back(particleContact);	
			}


		//check if the particle hits the left size of the ground when it's in the water
		if (m_blob[i]->getPosition().getX() < particuleSize && m_blob[i]->getPosition().getX() >= 0  && m_blob[i]->getPosition().getY() <= ( m_groundHeight + m_waterHeight) / 2)
		{
			float penetration = radius - m_blob[i]->getPosition().getX();
			Vecteur3D normal = Vecteur3D(1.0, 0.0, 0.0);
			ParticleContact* particleContact = new ParticleContact(m_blob[i], NULL, 0.5, penetration, normal);
			m_contactRegistry.push_back(particleContact);
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
	m_contactRegistry = vector<ParticleContact*>();
	
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

	//chek if we need cables CHANGER AVEC LE RESOLVER DE CONTACT 
	for (int i = 0; i < m_cables.size(); i++) {
		ParticleContact* contacts = new ParticleContact();
		unsigned numContactsGround = m_cables[i]->addContact(contacts);
		if (numContactsGround == 1) {
			//this means that the distance between the two particles is > maxlenght
			vector<ParticleContact*> contactArray;
			contactArray.push_back(contacts);
			m_resolver.resolveContacts(contactArray);
		}
	}
	
	checkWaterInteractions();
	
	m_forceRegistry.UpdateForce(deltaTime); //update each force 


	for (int i = 0; i < m_nbParticules; i++) {
		m_blob[i]->integrate(deltaTime);
	}
	
	checkParticleCollisions();
	checkGroundCollisions();

	m_resolver.resolveContacts(m_contactRegistry);

	m_forceRegistry.clear();

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