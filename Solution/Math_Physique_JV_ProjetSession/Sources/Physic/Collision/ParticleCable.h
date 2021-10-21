#pragma once
#ifndef DEF_PARTICLECABLE
#define DEF_PARTICLECABLE

#include "ParticleContact.h"
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	float maxLenght;
	float restitution;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

#endif