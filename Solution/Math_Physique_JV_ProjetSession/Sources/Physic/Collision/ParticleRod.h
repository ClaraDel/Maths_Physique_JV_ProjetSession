#pragma once
#ifndef DEF_PARTICLEROD
#define DEF_PARTICLEROD
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
public:
	double lenght;

public:

	virtual unsigned addContact(ParticleContact* contact) override;

};

#endif