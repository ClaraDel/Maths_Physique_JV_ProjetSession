#pragma once
#ifndef DEF_PARTICULEBUOYANCY
#define DEF_PARTICULEBUYOANCY
#include "../../Objects/Particule.h"
#include"ParticleForceGenerator.h"


class ParticleBuoyancy : public ParticleForceGenerator
{
private:
	//particle properties
	float m_particuleSize;
	double m_volume;
	double m_maxDepth;

	//effect properties
	double m_waterHeight;
	double m_liquidDensity;

public:
	ParticleBuoyancy(float particuleSize, double volume, double waterHeight, double liquidDensity);
	//apply Buoyancy based on particle position
	void UpdateForce(Particule* particule, double duration);
};

#endif