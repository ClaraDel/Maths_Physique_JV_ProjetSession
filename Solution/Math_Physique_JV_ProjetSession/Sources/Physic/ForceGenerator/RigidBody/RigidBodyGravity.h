#pragma once
#ifndef DEF_RIGIDBODYGRAVITY
#define DEF_RIGIDBODYGRAVITY
#include"../../Objects/RigidBody.h"
#include"RigidBodyForceGenerator.h"

class RigidBodyGravity : public RigidBodyForceGenerator
{
private:
	Vecteur3D m_gravity;

public:
	RigidBodyGravity();
	void UpdateForce(RigidBody* rigidBody, double duration);
};

#endif