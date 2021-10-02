#pragma once
#ifndef DEF_PARTICULEFORCEREGISTRY
#define DEF_PARTICULEFORCEREGISTRY
#include "../Particule.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry 
{
private:
	
	struct ParticleForceEntry
	{
		Particule* particule;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry registry;

public:
	//Registry accessors

	void UpdateForce(double duration);
};

#endif