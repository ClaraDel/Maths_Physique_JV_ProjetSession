#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <string>
#include "Game3a.h"
#include <ctime>

#define ProjectileMax 7
#define PI 3.14159265
using namespace std;

Game3a::Game3a(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{	
	formSize = Vecteur3D();
	rvbColor = Vecteur3D();
	m_registry = RigidBodyForceRegistry();
	rbTabl = vector<RigidBody*>();
	rbChosen = 0;
}

void Game3a::drawRigidBody(RigidBody* rigidbody) {
	Vecteur3D position;
	position = rigidbody->getPosition();

	glColor3f(rvbColor.getX(), rvbColor.getY(), rvbColor.getZ());
	glPushMatrix();
	
	glTranslatef(position.getX(), position.getY(), position.getZ());

	//choose the shape of the rigidbody 
	switch (shapeOfRb) {
	case 1:
		//a cube
		//parameters: size
		
		glMatrixMode(GL_MODELVIEW);
		
		glRotatef(2*acos(rigidbody->getOrientation().getW())*180.0/PI, rigidbody->getOrientation().getX(), rigidbody->getOrientation().getY(), rigidbody->getOrientation().getZ());
		glutSolidCube(formSize.getX());
		break;

	case 2:
		//a torus
		glRotatef(45.0, 1.0, 0.0, 0.0);
		//parameters: Inner radius of the torus, Outer radius of the torus, Number of sides for each radial section, 
		//Number of radial divisions for the torus
		glutSolidTorus(formSize.getX(), formSize.getY(), formSize.getZ(), 100);
		break;
	default:
		break;
	}
	glPopMatrix();

	//we don't want to store more than 20 rigidBody
	if (rbTabl.size() > 20) {
		rbTabl.erase(rbTabl.begin());
	}
}


void Game3a::doKeyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 97: // 'a' key
		rbChosen = (rbChosen + 1) % ProjectileMax;
		break;
	case 32: //space bar
		createRigidBody();
		break;
	case 27: //escape
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}


void Game3a::createRigidBody() {
	cout << endl; 
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH" << endl;
	RigidBody* rb;
	switch (rbChosen) {
	case 0: {
		//cube
		Vecteur3D position = Vecteur3D(0 , 1, 2);
		formSize = Vecteur3D(1, 1, 1);
		double masse = 5;
		double dx = formSize.getX();
		double dy = formSize.getY();
		double dz = formSize.getZ();
		double i00 = (1.0/12.0) * masse * (dy*dy + dz*dz);
		double i11 = (1.0/12.0) * masse * (dx*dx + dz*dz);
		double i22 = (1.0/12.0) * masse * (dx*dx + dy*dy);
		Matrix33 Inertia = Matrix33(i00, 0.0, 0.0, 0.0, i11, 0.0, 0.0, 0.0, i22);
		Matrix33 inverseInertia = Inertia.Inverse();
		//RigidBody(Vecteur3D pos, Vecteur3D vit, double m, Quaternion orientation, double damping, Vecteur3D angVelocity, double angularDamping, Matrix33 inverseInertia)
		rb =  new RigidBody(Vecteur3D(0, 1, 2), Vecteur3D(),masse,Quaternion(0,0.5,0,0), 0.99, Vecteur3D(),0.99, inverseInertia);
		shapeOfRb = 1;
		rvbColor = Vecteur3D(2.0, 0.5, 1);
		
		rbTabl.push_back(rb);
		m_registry.add(rb, new RigidBodyGravity());
		rb->addForceAtBodyPoint(Vecteur3D(-200, 3000, -1500), Vecteur3D(0.4,0,0.5));
		break;
	}
	default:
		break;
	}
}

//updates the position, acceleration and speed of 
//each particle in the game in each frame time
void Game3a::doUpdatePhysics() {

	double deltaTime = updateTime();

	m_registry.UpdateForce(deltaTime); //update each force 

	for (int i = 0; i < rbTabl.size(); i++) {
		//calculates with respect to the position and speed of the previous frame 
		rbTabl[i]->integrate(deltaTime); 
		
	}

	glutPostRedisplay();
}

//overload of the glut method "glutDisplayFunc. 
//Is executed at each frame
void Game3a::doDisplay() {
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(X, 1, Z, 0.0, 1.0, 0.0,0.0,1.0, 0.0); 

	// rotate of beta along the axes X
	glRotatef(beta, 1, 0, 0);

	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 

	for (int i = 0; i < rbTabl.size(); i++) {
		// draw each rigidbody contain in the rigidbody board
		cout << rbTabl[i]->getPosition() << endl;
		drawRigidBody(rbTabl[i]);
	}
	
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();
	
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
	
}


int Game3a::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Demo of rotation");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}