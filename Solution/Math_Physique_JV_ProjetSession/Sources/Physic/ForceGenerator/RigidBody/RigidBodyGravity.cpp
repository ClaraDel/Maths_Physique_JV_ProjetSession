#include "RigidBodyGravity.h"

using namespace std;

RigidBodyGravity::RigidBodyGravity() {
	m_gravity = Vecteur3D(0, -10, 0);
}

void RigidBodyGravity::UpdateForce(RigidBody* rigidBody, double duration)
{	
	//we check if the particle does not have infinite mass
	if (rigidBody->getMasse() == 0) return;
	rigidBody->addForce(rigidBody->getMasse() * m_gravity);
}