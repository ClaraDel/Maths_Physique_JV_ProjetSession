#pragma once
#ifndef DEF_PARTICLELINK
#define DEF_PARTICLELINK
#include "../Particule.h"
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
public:
	Particule* particule[2];

	double currentLenght() const;
	virtual unsigned int addContact(ParticleContact* contact) = 0;

};

#endif