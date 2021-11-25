#pragma once
#ifndef DEF_PARTICLECONTACTGENERATOR
#define DEF_PARTICLECONTACTGENERATOR
#include "ParticleContact.h"

//abstract class
class ParticleContactGenerator
{
public:
	virtual unsigned int addContact(ParticleContact* contact) = 0;
};


#endif



