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

	void resolveContacts(ParticleContact* contactArray,
		unsigned int numContact,
		float duraction);
};

#endif