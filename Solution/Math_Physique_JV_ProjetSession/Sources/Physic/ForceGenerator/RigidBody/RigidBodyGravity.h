#pragma once
#ifndef DEF_PARTICULEGRAVITY
#define DEF_PARTICULEGRAVITY
#include"../../RigidBody.h"
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