#pragma once
#include "ParticleContact.h"
class ParticleContactGenerator
{
	public:
		virtual unisgned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
}




