#pragma once
#ifndef DEF_PARTICULEDRAG
#define DEF_PARTICULEDRAG
#include "../../Particule.h"
#include"ParticleForceGenerator.h"

class ParticleDrag: public ParticleForceGenerator
{
private:
	//drag coefficients
	double m_k1;
	double m_k2;

public:
	ParticleDrag(double k1, double k2);
	void UpdateForce(Particule* particule, double duration);
};

#endif