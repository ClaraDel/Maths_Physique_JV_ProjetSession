#pragma once
#ifndef DEF_PARTICLECONTACTRESOLV
#define DEF_PARTICLECONTACTRESOLV
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	//number of allowed interaction
	unsigned int nbIterations;
	unsigned int iteractionsUsed;

public:
	// resolve each contact according to their separatingVelocity
	void resolveContacts(std::vector<ParticleContact*>  particuleContactList);
};

#endif