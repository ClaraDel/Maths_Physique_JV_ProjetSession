#pragma once
#ifndef DEF_PARTICULEGRAVITY
#define DEF_PARTICULEGRAVITY
#include"../Particule.h"
#include"ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
private:
	//anchor
	Vecteur3D gravity;

public:
	ParticleGravity();
	void UpdateForce(Particule* particule, double duration);
};

#endif