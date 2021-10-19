#pragma once
#ifndef DEF_PARTICLEROD
#define DEF_PARTICLEROD

class ParticleRod : public ParticleLink
{
public:
	double lenght;

public:

	virtual unisgned addContact(ParticleContact* contact, unsigned limit) const;

};

#endif