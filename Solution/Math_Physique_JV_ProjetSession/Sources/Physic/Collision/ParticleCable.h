#pragma once
#ifndef DEF_PARTICLECABLE
#define DEF_PARTICLECABLE

#include "ParticleContact.h"

class ParticleCable : public ParticleLink 
{
public :
	float maxLength;
	float restitution;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
}

#endif