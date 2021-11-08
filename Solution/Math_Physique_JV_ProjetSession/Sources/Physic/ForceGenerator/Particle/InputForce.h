#pragma once
#ifndef DEF_CONSTANTFORCE
#define DEF_CONSTANTFORCE
#include "../../Particule.h"
#include"ParticleForceGenerator.h"

class InputForce : public ParticleForceGenerator
{
private:
	Vecteur3D m_force;

public:
	InputForce(const Vecteur3D& force = Vecteur3D());
	Vecteur3D getForce();
	void changeForceValue(double xValue, double yValue, double zValue);
	void UpdateForce(Particule* particule, double duration);
};

#endif