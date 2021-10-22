#pragma once
#ifndef DEF_PARTICLECABLE
#define DEF_PARTICLECABLE

#include "ParticleContact.h"
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	float maxLenght;

	ParticleCable(Particule* p1, Particule* p2, float length);
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
	ParticleCable(Particule* p1, Particule* p2, float maxLenght);
};

#endif