#pragma once
#ifndef DEF_INPUTFORCEATPOINT
#define DEF_INPUTFORCEATPOINT

#include "RigidBodyForceGenerator.h"
#include "../../../Math/Vecteur3D.h"

class InputForceAtPoint : public RigidBodyForceGenerator{
private:
	bool m_launch;
	Vecteur3D m_force;
	Vecteur3D m_pos;

public:
	InputForceAtPoint(Vecteur3D force, Vecteur3D pointPos);
	void UpdateForce(RigidBody* rigidBody, double duration);

};

#endif
