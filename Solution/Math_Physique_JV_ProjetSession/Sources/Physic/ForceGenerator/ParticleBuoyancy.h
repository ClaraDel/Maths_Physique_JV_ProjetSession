#pragma once
#ifndef DEF_PARTICULEBUOYANCY
#define DEF_PARTICULEBUYOANCY
#include"../Particule.h"
#include"ParticleForceGenerator.h"


class ParticleBuoyancy : public ParticleForceGenerator
{
private:
	//particle properties
	double m_maxDepth;
	double m_volume;

	//effect properties
	double m_waterHeight;
	double m_liquidDensity;

public:
	ParticleBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity);
	//apply Buoyancy based on particle position
	void UpdateForce(Particule* particule, double duration);
};

#endif