/*#include "RigidBodyContact.h"

RigidBodyContact::RigidBodyContact(){
}

//calculate the separating velocity
double RigidBodyContact::calculateSeperatingVelocity(RigidBody* r1, RigidBody* r2) {
    Vecteur3D distanceVect = r1->getPosition() - r2->getPosition();
    Vecteur3D contactNormal = distanceVect.normalization();
    
	return (r1->getVelocity() - r2->getVelocity() ).scalarProduct(m_contactNormal);
}*/