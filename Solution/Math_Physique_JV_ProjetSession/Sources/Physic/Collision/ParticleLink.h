#pragma once
#include "../Particule.h"
class ParticleLink : public ParticleContactGenerator
{
public:
	Particule* particule[2];

	float currentLength() const;
	unisgned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

}