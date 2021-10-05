#pragma once
#ifndef DEF_CONSTANTFORCE
#define DEF_CONSTANTFORCE
#include"../Particule.h"
#include"ParticleForceGenerator.h"

class ConstantForce : public ParticleForceGenerator
{
private:
	Vecteur3D m_force;

public:
	ConstantForce(const Vecteur3D& force);
	void UpdateForce(Particule* particule, double duration);
};

#endif