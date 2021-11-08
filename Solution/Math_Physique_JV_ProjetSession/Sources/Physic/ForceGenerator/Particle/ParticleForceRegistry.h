#pragma once
#ifndef DEF_PARTICULEFORCEREGISTRY
#define DEF_PARTICULEFORCEREGISTRY
#include "../../Particule.h"
#include "ParticleForceGenerator.h"
#include "InputForce.h"

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
	ParticleForceRegistry();
	InputForce* getInputForce();
	void clear();
	void add(Particule* particule, ParticleForceGenerator* particuleFg);
	void remove(Particule* particule, ParticleForceGenerator* particuleFg);
	void UpdateForce(double duration);
};

#endif