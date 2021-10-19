#pragma once
#ifndef DEF_PARTICLECONTACTGENERATOR
#define DEF_PARTICLECONTACTGENERATOR
#include "ParticleContact.h"


class ParticleContactGenerator
{
public:
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};


#endif



