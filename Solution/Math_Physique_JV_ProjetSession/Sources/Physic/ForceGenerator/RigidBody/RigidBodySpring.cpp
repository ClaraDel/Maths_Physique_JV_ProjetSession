#include "RigidBodySpring.h"

using namespace std;

RigidBodySpring::RigidBodySpring(const Vecteur3D &connectionPoint, RigidBody* other, const Vecteur3D &otherConnectionPoint, double k, double l0){
    m_connectionPoint = connectionPoint ; 
    m_otherRigidBody = other ;
    m_otherConnectionPoint = otherConnectionPoint;
    m_k = k;
    m_l0 = l0;
}

void RigidBodySpring::UpdateForce(RigidBody* rigidBody, double duration)
{
    //converts local coordinates to global coordinates
    Vecteur3D worldConnectionPoint = rigidBody->getPointInWorldSpace(m_connectionPoint);
    Vecteur3D worldOtherConnectionPoint = m_otherRigidBody->getPointInWorldSpace(m_otherConnectionPoint);


	Vecteur3D currentLenght = worldConnectionPoint - worldOtherConnectionPoint ;

	//Hooke's Law
	force  = -m_k  * ((currentLenght).norm() - m_l0)  *  (currentLenght).normalization();
	RigidBody->addForce(force);
}