#include "RigidBody.h"

//create transform matrix from position and orientation

RigidBody::RigidBody(Vecteur3D pos, Vecteur3D vit, double m, Quaternion orientation, double damping, Vecteur3D angVelocity, double angularDamping, Matrix33 inverseInertia){ //a changer!

	
	m_forceApplied = Vecteur3D();
	m_position = pos;
	m_velocity = vit;
	m_vit_angular = Vecteur3D();
	m_acceleration = Vecteur3D();
	m_angularAcceleration = Vecteur3D();
	m_damping = damping;
	m_angularDamping = angularDamping;
	m_forceApplied = Vecteur3D();
	m_toqueApplied = Vecteur3D();
	m_orientation = orientation;
	m_angVelocity = angVelocity ;
	m_transformMatrix = Matrix34();
	m_inverseInertia = inverseInertia;
	m_inverseInertiaWorld = Matrix33();
	m_angularDamping = angularDamping;

	if(m!=0){
		m_inverseMasse = 1/m;
	} else {
		m_inverseMasse = 0;
	}
}
RigidBody::~RigidBody()
{
}

void RigidBody::calculateTransformMatrix(Matrix34 &transformMatrix, const Vecteur3D &position, const Quaternion &orientation) {
	double w = orientation.getW();
	double x = orientation.getX();
	double y = orientation.getY();
	double z = orientation.getZ();
	double xy = 2* x * y;
	double zw = 2* z * w;
	double xz = 2* x * z;
	double yw = 2 * y * w;
	double yz = 2 * y * z;
	double xw = 2 * x * w;
	double x2 = 2 * x * x;
	double y2 = 2 * y * y;
	double z2 = 2 * z * z;
	transformMatrix.setValue(0, 1 - (y2 + z2));
	transformMatrix.setValue(1, xy + zw);
	transformMatrix.setValue(2, xz + yw);
	transformMatrix.setValue(3, position.getX());
	transformMatrix.setValue(4, xy - zw);
	transformMatrix.setValue(5, 1 - (x2 + z2));
	transformMatrix.setValue(6, yz + xw);
	transformMatrix.setValue(7, position.getY());
	transformMatrix.setValue(8, xz + yw);
	transformMatrix.setValue(9, yz - xw);
	transformMatrix.setValue(10, 1 - (x2 + y2));
	transformMatrix.setValue(11, position.getZ());
}

void RigidBody::calculateTransformInertia(Matrix33& iitWorld, const Quaternion& q, const Matrix33& iitBody, const Matrix34& rotmat){
	double t4 = rotmat.getValue(0) * iitBody.getValue(0) + rotmat.getValue(1) * iitBody.getValue(3) + rotmat.getValue(2) * iitBody.getValue(6);
	double t9 =  rotmat.getValue(0) * iitBody.getValue(1) + rotmat.getValue(1) * iitBody.getValue(4) + rotmat.getValue(2) * iitBody.getValue(7);
	double t14 =  rotmat.getValue(0) * iitBody.getValue(2) + rotmat.getValue(1) * iitBody.getValue(5) + rotmat.getValue(2) * iitBody.getValue(8);
	double t28 =  rotmat.getValue(4) * iitBody.getValue(0) + rotmat.getValue(5) * iitBody.getValue(3) + rotmat.getValue(6) * iitBody.getValue(6);
	double t33 =  rotmat.getValue(4) * iitBody.getValue(1) + rotmat.getValue(5) * iitBody.getValue(4) + rotmat.getValue(6) * iitBody.getValue(7);
	double t38 =  rotmat.getValue(4) * iitBody.getValue(2) + rotmat.getValue(5) * iitBody.getValue(5) + rotmat.getValue(6) * iitBody.getValue(8);
	double t52 =  rotmat.getValue(8) * iitBody.getValue(0) + rotmat.getValue(9) * iitBody.getValue(3) + rotmat.getValue(10) * iitBody.getValue(6);
    double t57 =  rotmat.getValue(8) * iitBody.getValue(1) + rotmat.getValue(9) * iitBody.getValue(4) + rotmat.getValue(10) * iitBody.getValue(7);
	double t62 =  rotmat.getValue(8) * iitBody.getValue(2) + rotmat.getValue(9) * iitBody.getValue(5) + rotmat.getValue(10) * iitBody.getValue(8);
	iitWorld.setValue(0, t4*rotmat.getValue(0) + t9*rotmat.getValue(1) + t14*rotmat.getValue(2));
	iitWorld.setValue(1,  t4*rotmat.getValue(4) + t9*rotmat.getValue(5) + t14*rotmat.getValue(6));
	iitWorld.setValue(2, t4*rotmat.getValue(8) + t9*rotmat.getValue(9) + t14* rotmat.getValue(10));
	iitWorld.setValue(3, t28*rotmat.getValue(0) + t33*rotmat.getValue(1) + t38*rotmat.getValue(2));
	iitWorld.setValue(4,  t28*rotmat.getValue(4) + t33*rotmat.getValue(5) + t38*rotmat.getValue(6));
	iitWorld.setValue(5, t28*rotmat.getValue(8) + t33*rotmat.getValue(9) + t38*rotmat.getValue(10));
	iitWorld.setValue(6 ,t52*rotmat.getValue(0)+ t57*rotmat.getValue(1) + t62*rotmat.getValue(2));
	iitWorld.setValue( 7,t52*rotmat.getValue(4) + t57*rotmat.getValue(5) + t62*rotmat.getValue(6));
	iitWorld.setValue(8 , t52*rotmat.getValue(8) + t57*rotmat.getValue(9) + t62*rotmat.getValue(10));

}

//calculate the transform Matrix for the RigidBody
void RigidBody::calculateDerivedData(){
    m_orientation.normalize();
    calculateTransformMatrix(m_transformMatrix, m_position, m_orientation);
	calculateTransformInertia(m_inverseInertiaWorld,m_orientation,m_inverseInertia, m_transformMatrix);
}

void RigidBody::addForce(Vecteur3D forceToAdd) {
	m_forceApplied += forceToAdd;
}

//integrate the chosen vector and update its value
void RigidBody::updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector){
	vector += deltaTime * integrateVector ;
}

void RigidBody::integrate(double deltaTime){

	accelerationCalcul();
	m_angularAcceleration = m_inverseInertiaWorld * m_toqueApplied;
	updateVector(m_acceleration, deltaTime, m_velocity); //calculates the new velocity
	updateVector(m_angularAcceleration, deltaTime, m_vit_angular); //calculates the new angular velocity
	m_velocity *= pow(m_damping, deltaTime);
	m_vit_angular *= pow(m_angularDamping,deltaTime);
	updateVector(m_velocity, deltaTime, m_position); //calculates the new position
	//updateVector(m_vit_angular, deltaTime, m_orientation); //calculates the new orientation
	calculateDerivedData();
	m_forceApplied = Vecteur3D();
}

//Application of Newton's law
void RigidBody::accelerationCalcul() {
	m_acceleration = m_inverseMasse * m_forceApplied ;
}

double RigidBody::getInverseMasse() const{
	return m_inverseMasse;
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