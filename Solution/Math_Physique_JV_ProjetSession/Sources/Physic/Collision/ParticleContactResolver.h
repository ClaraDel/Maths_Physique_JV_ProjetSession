#pragma once
#ifndef DEF_PARTICLECONTACTRESOLV
#define DEF_PARTICLECONTACTRESOLV

class ParticleContactResolver
{
protected :
	//number of allowed interaction
	unsigned int interaction;

public :

	void resolveContacts(ParticleContact* contactArray,
		unsigned int numContact,
		float duraction);
}

#endif