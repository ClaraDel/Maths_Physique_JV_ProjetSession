#pragma once
#ifndef DEF_RIGIDBODYSPRING
#define DEF_RIGIDBODYSPRING
#include "../../../RigidBody.h"
#include"RigidBodyForceGenerator.h"

class RigidBodySpring : public RigidBodyForceGenerator
{
private:
    //point of connection of spring in local coordinate
    Vecteur3D m_connectionPoint ;

    //point of connection of spring of other RigidBody in local coordinate
    Vecteur3D m_otherConnectionPoint ;

    RigidBody* m_otherRigidBody  = nullptr ;

    //Spring constant
	double m_k;
	double m_l0;

public:
	RigidBodySpring(const Vecteur3D &connectionPoint, RigidBody* other, const Vecteur3D &otherConnectionPoint, double k, double l0);

	//apply spring force to the rigidBody
	void UpdateForce(RigidBody* rigidBody, double duration);
};

#endif