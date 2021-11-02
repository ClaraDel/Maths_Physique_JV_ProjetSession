#pragma once
#ifndef DEF_PARTICLECONTACTREGISTRY
#define DEF_PARTICLECONTACTREGISTRY

#include "../Particule.h"
#include "ParticleContact.h"
#include "ParticleCable.h"
#include <vector>

class ParticleContactRegistry {

private :

	std::vector<ParticleContact*> m_contactList;

	
public :

	ParticleContactRegistry();
	std::vector<ParticleContact*> getContactList();
	void clear();
	void add(ParticleContact* particuleContact);
	void remove(ParticleContact* particuleContact);
	void updateContact(std::vector<Particule*> particuleList, std::vector<ParticleCable*> cableList, double particuleSize, double particuleRestitution, double groundHeight, double waterHeight);
	void checkGroundCollision(std::vector<Particule*> particuleList, double particuleSize, double groundHeight, double waterHeight);
	void checkParticlesCollision(std::vector<Particule*> particuleList, double particuleSize, double particuleRestitution);
	void checkCableCollision(std::vector<ParticleCable*> cableList);

};


#endif