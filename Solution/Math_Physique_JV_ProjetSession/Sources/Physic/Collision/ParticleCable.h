#pragma once
#ifndef DEF_PARTICLECABLE
#define DEF_PARTICLECABLE

#include "ParticleContact.h"
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	float maxLenght;

	//return 1 if there is a Cable and assign the correct information at ParticleContact
	unsigned int addContact(ParticleContact* contact) override;
	ParticleCable(Particule* p1, Particule* p2, float maxLenght);
};

#endif