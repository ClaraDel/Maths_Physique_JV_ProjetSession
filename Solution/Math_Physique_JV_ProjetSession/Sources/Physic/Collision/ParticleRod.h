#pragma once
#ifndef DEF_PARTICLEROD
#define DEF_PARTICLEROD
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
	double lenght;

public:
	//return 1 if there is a Rod and assign the correct information at ParticleContact
	virtual unsigned addContact(ParticleContact* contact) override;

};

#endif