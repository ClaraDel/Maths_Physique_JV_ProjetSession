#include "RigidBody.h"

using namespace std;


RigidBody::RigidBody(Vecteur3D pos, Vecteur3D vit, double m, Quaternion orientation, double damping, Vecteur3D angVelocity, double angularDamping, Matrix33 inverseInertia){ 

	
	m_position = pos;
	m_velocity = vit;
	m_acceleration = Vecteur3D();

	m_orientation = orientation;
	m_vit_angular = angVelocity ;
	m_angularAcceleration = Vecteur3D();

	m_damping = damping;
	m_angularDamping = angularDamping;
	
	
	m_inverseInertia = inverseInertia;
	m_transformMatrix = Matrix34();
	m_inverseInertiaWorld = Matrix33();


	if(m!=0){
		m_inverseMasse = 1/m;
	} else {
		m_inverseMasse = 0;
	}

	calculateDerivedData();

	m_forceApplied = Vecteur3D();
	m_torqueApplied = Vecteur3D();
}

RigidBody::~RigidBody()
{
}


//create transform matrix from position and orientation
void RigidBody::calculateTransformMatrix() {
	double w = m_orientation.getW();
	double x = m_orientation.getX();
	double y = m_orientation.getY();
	double z = m_orientation.getZ();
	double xy = 2* x * y;
	double zw = 2* z * w;
	double xz = 2* x * z;
	double yw = 2 * y * w;
	double yz = 2 * y * z;
	double xw = 2 * x * w;
	double x2 = 2 * x * x;
	double y2 = 2 * y * y;
	double z2 = 2 * z * z;
	m_transformMatrix.setValue(0, 1 - (y2 + z2));
	m_transformMatrix.setValue(1, xy + zw);
	m_transformMatrix.setValue(2, xz + yw);
	m_transformMatrix.setValue(3, m_position.getX());
	m_transformMatrix.setValue(4, xy - zw);
	m_transformMatrix.setValue(5, 1 - (x2 + z2));
	m_transformMatrix.setValue(6, yz + xw);
	m_transformMatrix.setValue(7, m_position.getY());
	m_transformMatrix.setValue(8, xz + yw);
	m_transformMatrix.setValue(9, yz - xw);
	m_transformMatrix.setValue(10, 1 - (x2 + y2));
	m_transformMatrix.setValue(11, m_position.getZ());
}
//transform the inverse of local inertia matrix on the inverse of the inertia matrix in world coodinate
void RigidBody::calculateTransformInertia(){
	double t4 = m_transformMatrix.getValue(0) * m_inverseInertia.getValue(0) + m_transformMatrix.getValue(1) * m_inverseInertia.getValue(3) + m_transformMatrix.getValue(2) * m_inverseInertia.getValue(6);
	double t9 =  m_transformMatrix.getValue(0) * m_inverseInertia.getValue(1) + m_transformMatrix.getValue(1) * m_inverseInertia.getValue(4) + m_transformMatrix.getValue(2) * m_inverseInertia.getValue(7);
	double t14 =  m_transformMatrix.getValue(0) * m_inverseInertia.getValue(2) + m_transformMatrix.getValue(1) * m_inverseInertia.getValue(5) + m_transformMatrix.getValue(2) * m_inverseInertia.getValue(8);
	double t28 =  m_transformMatrix.getValue(4) * m_inverseInertia.getValue(0) + m_transformMatrix.getValue(5) * m_inverseInertia.getValue(3) + m_transformMatrix.getValue(6) * m_inverseInertia.getValue(6);
	double t33 =  m_transformMatrix.getValue(4) * m_inverseInertia.getValue(1) + m_transformMatrix.getValue(5) * m_inverseInertia.getValue(4) + m_transformMatrix.getValue(6) * m_inverseInertia.getValue(7);
	double t38 =  m_transformMatrix.getValue(4) * m_inverseInertia.getValue(2) + m_transformMatrix.getValue(5) * m_inverseInertia.getValue(5) + m_transformMatrix.getValue(6) * m_inverseInertia.getValue(8);
	double t52 =  m_transformMatrix.getValue(8) * m_inverseInertia.getValue(0) + m_transformMatrix.getValue(9) * m_inverseInertia.getValue(3) + m_transformMatrix.getValue(10) * m_inverseInertia.getValue(6);
    double t57 =  m_transformMatrix.getValue(8) * m_inverseInertia.getValue(1) + m_transformMatrix.getValue(9) * m_inverseInertia.getValue(4) + m_transformMatrix.getValue(10) * m_inverseInertia.getValue(7);
	double t62 =  m_transformMatrix.getValue(8) * m_inverseInertia.getValue(2) + m_transformMatrix.getValue(9) * m_inverseInertia.getValue(5) + m_transformMatrix.getValue(10) * m_inverseInertia.getValue(8);
	m_inverseInertiaWorld.setValue(0, t4*m_transformMatrix.getValue(0) + t9*m_transformMatrix.getValue(1) + t14*m_transformMatrix.getValue(2));
	m_inverseInertiaWorld.setValue(1,  t4*m_transformMatrix.getValue(4) + t9*m_transformMatrix.getValue(5) + t14*m_transformMatrix.getValue(6));
	m_inverseInertiaWorld.setValue(2, t4*m_transformMatrix.getValue(8) + t9*m_transformMatrix.getValue(9) + t14* m_transformMatrix.getValue(10));
	m_inverseInertiaWorld.setValue(3, t28*m_transformMatrix.getValue(0) + t33*m_transformMatrix.getValue(1) + t38*m_transformMatrix.getValue(2));
	m_inverseInertiaWorld.setValue(4,  t28*m_transformMatrix.getValue(4) + t33*m_transformMatrix.getValue(5) + t38*m_transformMatrix.getValue(6));
	m_inverseInertiaWorld.setValue(5, t28*m_transformMatrix.getValue(8) + t33*m_transformMatrix.getValue(9) + t38*m_transformMatrix.getValue(10));
	m_inverseInertiaWorld.setValue(6 ,t52*m_transformMatrix.getValue(0)+ t57*m_transformMatrix.getValue(1) + t62*m_transformMatrix.getValue(2));
	m_inverseInertiaWorld.setValue( 7,t52*m_transformMatrix.getValue(4) + t57*m_transformMatrix.getValue(5) + t62*m_transformMatrix.getValue(6));
	m_inverseInertiaWorld.setValue(8 , t52*m_transformMatrix.getValue(8) + t57*m_transformMatrix.getValue(9) + t62*m_transformMatrix.getValue(10));

}

//calculate the transform Matrix for the RigidBody
void RigidBody::calculateDerivedData(){
    m_orientation.normalize();
	//Calculate the transform Matrix 
    calculateTransformMatrix();
	//Calculate the inertiaTensor in world sapce
	calculateTransformInertia();
}

//add the force to our rigidbody
void RigidBody::addForce(Vecteur3D forceToAdd) {
	m_forceApplied += forceToAdd;
}

//integrate the chosen vector and update its value
void RigidBody::updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector){
	vector += deltaTime * integrateVector ;
}

//integrate the chosen quaternion and update its value 
void RigidBody::updateQuaternion(Vecteur3D const& integrateQuaternion, double deltaTime, Quaternion& m_orientation){
	Quaternion q = Quaternion(0,integrateQuaternion.getX(), integrateQuaternion.getY(), integrateQuaternion.getZ());
	q *= m_orientation;
	m_orientation += Quaternion(0.5*deltaTime*q.getW(),0.5*deltaTime*q.getX(),0.5*deltaTime*q.getY(),0.5*deltaTime*q.getZ());

}

void RigidBody::integrate(double deltaTime){

	//calcul linear acceleration p: = (1/m) *f
	accelerationCalcul();
	// calcul angular acceleration  theta: = I^-1 * torq
	m_angularAcceleration = m_inverseInertiaWorld * m_torqueApplied;
	//update linear velocity 
	updateVector(m_acceleration, deltaTime, m_velocity); //calculates the new velocity
	m_velocity *= pow(m_damping, deltaTime);
	//update angular velocity 
	updateVector(m_angularAcceleration, deltaTime,  m_vit_angular); //calculates the new angular velocity
	m_vit_angular *= pow(m_angularDamping,deltaTime);
	//update position
	updateVector(m_velocity, deltaTime, m_position); //calculates the new position
	//update orientation 
	updateQuaternion( m_vit_angular, deltaTime, m_orientation); //calculates the new orientation
	calculateDerivedData();	
	clearAccumulator();
}

//Application of Newton's law
void RigidBody::accelerationCalcul() {
	m_acceleration = m_inverseMasse * m_forceApplied ;
}

//add the force at a precise point in world coordinate
void RigidBody::addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint){

	Vecteur3D distance = worldPoint - m_position;
	m_forceApplied += force;
	m_torqueApplied += distance.vectorProduct(force);
}
//add the force at a point in local coordinate 
void RigidBody::addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& LocalPoint){
	Vecteur3D point = 	m_transformMatrix.TransformPosition(LocalPoint);
	addForceAtPoint(force, point);
}

// reset the force and toque applied 
void RigidBody::clearAccumulator(){
	m_forceApplied = Vecteur3D();
	m_torqueApplied = Vecteur3D();
}


double RigidBody::getInverseMasse() const{
	return m_inverseMasse;
}

double RigidBody::getMasse() const{
	return 1/m_inverseMasse;
}

Quaternion RigidBody::getOrientation() {
	return m_orientation;
}

Vecteur3D RigidBody::getAcceleration() {
	return m_acceleration;
}

Vecteur3D RigidBody::getVelocity() {
	return m_velocity;
}

void RigidBody::setInverseMasse(double value) {
	m_inverseMasse = value;
}


Vecteur3D RigidBody::getPosition() {
	return m_position;
}
void RigidBody::setPosition(Vecteur3D const& p) {
	m_position = p;
}

void RigidBody::setAcceleration(double const x, double const y, double const z) {
	m_acceleration = Vecteur3D(x, y, z);
}

void RigidBody::setVelocity(double const x, double const y, double const z) {
	m_velocity = Vecteur3D(x, y, z);
}

void RigidBody::setVelocity(Vecteur3D v) {
	m_velocity = v;
}

void RigidBody::setDamping(double d){
	m_damping = d;
}

