#pragma once
#ifndef DEF_PARTICULEGRAVITY
#define DEF_PARTICULEGRAVITY
#include"../Particule.h"
#include"ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private:
	Vecteur3D m_gravity;

public:
	ParticleGravity();
	void UpdateForce(Particule* particule, double duration);
};

#endif