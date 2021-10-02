#pragma once
#ifndef DEF_PARTICULEANCHOREDSPRING
#define DEF_PARTICULEANCHOREDSPRING
#include"../Particule.h"
#include"ParticleForceGenerator.h"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
	//particle properties
	double maxDepth;
	double volume;

	//effect properties
	double waterHeight;
	double liquidDensity;

public:
	//apply Buoyancy based on particle position
	void UpdateForce(Particule* particle, double duration);
};

#endif