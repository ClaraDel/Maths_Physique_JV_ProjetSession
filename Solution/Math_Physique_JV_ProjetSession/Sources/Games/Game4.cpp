#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <string>
#include "Game4.h"
#include <ctime>


#define PI 3.14159265
#define MaxDirection 3

using namespace std;


Game4::Game4(string nameGame, string descriptionGame) : GameBase(nameGame, descriptionGame)
{
	m_primitives = vector<Primitive*>();
	createWalls();
	m_tree = OcTree(3, 10, 3);
	m_cube = 0;
	m_formSize = Vecteur3D();
	m_rvbColor = Vecteur3D();
	directionChosen = 0;
	m_registry = RigidBodyForceRegistry();
	pause_game = false;
	X = 0.1;
	Z = 0.0;
	Y = 20.0;
}


void Game4::doKeyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 97: // 'a' key
		directionChosen = (directionChosen + 1) % MaxDirection;
		break;
	case 32: //space bar
		launchDemo();
		break;
	case 27: //escape
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

//Draw our cube
void Game4::drawCube() {
	if (m_cube != nullptr) {
		Vecteur3D position;
		position = m_cube->getPosition();
		glColor3f(m_rvbColor.getX(), m_rvbColor.getY(), m_rvbColor.getZ());
		glPushMatrix();

		glTranslatef(position.getX(), position.getY(), position.getZ());

		glMatrixMode(GL_MODELVIEW);
		//Rotate it with the calculate quaternion
		glRotatef(2 * acos(m_cube->getOrientation().getW()) * 180.0 / PI, m_cube->getOrientation().getX(), m_cube->getOrientation().getY(), m_cube->getOrientation().getZ());
		glutSolidCube(m_formSize.getX());

		glPopMatrix();
	}
}

//Draw the walls of the room
void Game4::drawWalls() {

	//Draw ground EXAMPLE GAME2

	glColor3f(0.0, 0.0, 1.0); //roof blue
	glBegin(GL_POLYGON);
	glVertex3f(0, 10, -5);
	glVertex3f(10, 10, -5);
	glVertex3f(10, 10, 5);
	glVertex3f(0, 10, 5);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); //back red
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -5);
	glVertex3f(0, 10, -5);
	glVertex3f(0.0, 10, 5);
	glVertex3f(0.0, 0.0, 5);
	glEnd();

	glColor3f(0.0, 1.0, 0.0); //left wall green
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 5);
	glVertex3f(10, 0, 5);
	glVertex3f(10, 10, 5);
	glVertex3f(0, 10, 5);
	glEnd();

	glColor3f(0.1, 0.0, 0.0); //right wall brown 
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -5);
	glVertex3f(10, 0, -5);
	glVertex3f(10, 10, -5);
	glVertex3f(0, 10, -5);
	glEnd();

	glColor3f(1.0, 0.0, 1.0); //ground purple
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -5);
	glVertex3f(10, 0, -5);
	glVertex3f(10, 0, 5);
	glVertex3f(0, 0, 5);
	glEnd();
	
	
	
	
}

void Game4::createWalls(){
	m_primitives.push_back(new Plane(Vecteur3D(0,5,0),Vecteur3D(1,0,0)));
	m_primitives.push_back(new Plane(Vecteur3D(5,5,-5),Vecteur3D(0,0,1)));
	m_primitives.push_back(new Plane(Vecteur3D(5,5,5),Vecteur3D(0,0,-1)));
	m_primitives.push_back(new Plane(Vecteur3D(5,0,0),Vecteur3D(0,1,0)));
	m_primitives.push_back(new Plane(Vecteur3D(5,10,0),Vecteur3D(0,-1,0)));

}

void Game4::createCube(Vecteur3D force ) {
	m_formSize = Vecteur3D(1, 1, 1);
	double masse = 5;
	double dx = m_formSize.getX();
	double dy = m_formSize.getY();
	double dz = m_formSize.getZ();
	double i00 = (1.0 / 12.0) * masse * (dy * dy + dz * dz);
	double i11 = (1.0 / 12.0) * masse * (dx * dx + dz * dz);
	double i22 = (1.0 / 12.0) * masse * (dx * dx + dy * dy);
	//Calculate the Inertia Matrix for a cube 
	Matrix33 Inertia = Matrix33(i00, 0.0, 0.0, 0.0, i11, 0.0, 0.0, 0.0, i22);
	Matrix33 inverseInertia = Inertia.Inverse();
	//Create our rigidBody
	m_cube = new RigidBody(Vecteur3D(5, 5, 0), Vecteur3D(), masse, Quaternion(0, 0.5, 0, 0), 0.99, Vecteur3D(), 0.99, inverseInertia);
	m_rvbColor = Vecteur3D(2.0, 0.5, 1);

	//Add the gravity
	m_registry.add(m_cube, new RigidBodyGravity());
	//Add a Force to rotate our rigidbody 
	m_registry.add(m_cube, new InputForceAtPoint(force, Vecteur3D(0.4, 0, 0.5)));

	//Add to the octree
	m_primitives.push_back(new Sphere(m_cube,0.5));

}


void Game4::launchDemo() {

	if (m_cube != nullptr) {
		m_primitives.pop_back();
	}

	m_cube = nullptr;
	
	m_registry.clear();
	
	Vecteur3D force = Vecteur3D(-2, 20, -15);
	switch (directionChosen){
	case 0 :
		force += Vecteur3D(-(rand() % 10 + 1),0,0);
		break;
	case 1:
		force += Vecteur3D(0, (rand() % 10 + 1), 0);
		break;
	case 2:
		force += Vecteur3D(0, 0, -(rand() % 10 + 1));
		break;
	default :
		break;
	}
	createCube(force);
	
}


//updates the position, acceleration and speed of 
//the cube in each frame time
void Game4::doUpdatePhysics() {

	//cout << m_primitives.size() << endl;
	double deltaTime = updateTime();

	//check if there is a cube and if it's not already in collision with a wall

	if (m_cube != nullptr && !pause_game){//&& m_cube->getVelocity() != Vecteur3D()) {

		m_registry.UpdateForce(deltaTime); //update each force 

		//calculates with respect to the position and speed of the previous frame 
		m_cube->integrate(deltaTime);

		//UpdateOctree();
		m_tree.Build(m_primitives);
		vector<PossibleCollision> possibleCollisions = m_tree.getPossibleCollision();
		//à modifier

		for (int i = 0; i < possibleCollisions.size(); i++)
		{
			CollisionData data = possibleCollisions[i].narrowPhaseCollisions();

			//arrête la simulation si une collision a bien eu lieu
			PrintAndStop(data);
		}
		m_tree.Clear();
		
	}

	cout << " " << endl;
	cout << "new update physic" << endl;
	
	glutPostRedisplay();
}

void Game4::UpdateOctree(){
	
	
}

void Game4::PrintAndStop(CollisionData data){
	if (data != CollisionData()) {
		cout <<"Data"<< data;
		//on stop le cube
		pause_game = true;
		m_cube->setVelocity(0, 0, 0);
		m_cube->setAcceleration(0, 0, 0);
		m_cube->setAngularVelocity(0, 0, 0);
		m_cube->setAngularAcceleration(0, 0, 0);
	}
	
}

void Game4::doDisplay() {
	//clear buffer (indicate the buffer to clear)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//replaces the current matrix with the identity matrix
	glLoadIdentity(); 

	//specifies the position of the eye point, the reference point
	//and the direction of the up vector
	gluLookAt(20,5, 0, 5, 5, 0.0,0.0,1.0, 0.0); 
	
	//apply the fonction updatePhysics
	glutIdleFunc(updatePhysics); 

	drawWalls();
	drawCube();
	
	// swaps the buffers of the current window if double buffered
	glutSwapBuffers();
	
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);//background color 
	glEnable(GL_DEPTH_TEST);
	
}

int Game4::launch(int argc, char* argv[])
{
	//initialization of glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Bim bam boum");

	//give to glut our function for display, reshape, keyboard input and arrows management
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrows);

	glutMainLoop();
	return EXIT_SUCCESS;

}