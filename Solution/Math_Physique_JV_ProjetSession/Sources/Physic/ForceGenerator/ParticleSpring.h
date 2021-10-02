#pragma once
#ifndef DEF_PARTICULEANCHOREDSPRING
#define DEF_PARTICULEANCHOREDSPRING
#include"../Particule.h"
#include"ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	//other anchor
	Particule* m_other;
	//Spring constant
	double m_k;
	double m_l0;

public:
	ParticleSpring(Particule* other, double k, double l0);
	//apply Hooke's law based on particles position
	void UpdateForce(Particule* particule, double duration);
};

#endif