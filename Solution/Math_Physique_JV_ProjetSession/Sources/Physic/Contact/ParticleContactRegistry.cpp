#include "ParticleContactRegistry.h"

using namespace std;

ParticleContactRegistry::ParticleContactRegistry() {
	m_contactList = vector<ParticleContact*>();
}

void ParticleContactRegistry::add(ParticleContact* particuleContact)
{
	m_contactList.push_back(particuleContact);
}

vector<ParticleContact*> ParticleContactRegistry::getContactList()
{
	return m_contactList;
}

void ParticleContactRegistry::remove(ParticleContact* particuleContact) {
	//searching through registry the contact we want to erase
	for (int i = 0; i < m_contactList.size(); i++)
	{
		if (m_contactList[i] == particuleContact) {
			m_contactList.erase(m_contactList.begin() + i);
		}
	}

}

void ParticleContactRegistry::clear()
{
	m_contactList.clear();
}

void ParticleContactRegistry::checkGroundCollision(vector<Particule*> particuleList, double particuleSize, double groundHeight, double waterHeight) {
	for (int i = 0; i < particuleList.size(); i++) {
		float radius = particuleSize;
		float distance = particuleList[i]->getPosition().getY() - groundHeight;

		// check if the particule is above or under ground 
		if (distance <= radius && particuleList[i]->getPosition().getX() < 0 && particuleList[i]->getPosition().getX() >= -100)
		{
			float penetration = radius - distance;
			Vecteur3D normal = Vecteur3D(0.0, 1.0, 0.0);
			ParticleContact* particleContact = new ParticleContact(particuleList[i], NULL, 0.5, penetration, normal);
			add(particleContact);
		}


		//check if the particle hits the left size of the ground when it's in the water
		if (particuleList[i]->getPosition().getX() < particuleSize && particuleList[i]->getPosition().getX() >= 0 && particuleList[i]->getPosition().getY() <= (groundHeight + waterHeight) / 2)
		{
			float penetration = radius - particuleList[i]->getPosition().getX();
			Vecteur3D normal = Vecteur3D(1.0, 0.0, 0.0);
			ParticleContact* particleContact = new ParticleContact(particuleList[i], NULL, 0.5, penetration, normal);
			add(particleContact);
		}
	}
}


void ParticleContactRegistry::checkParticlesCollision(vector<Particule*> particuleList, double particuleSize, double particuleRestitution) {
	for (int i = 0; i < particuleList.size(); i++) {
		for (int j = i + 1; j < particuleList.size(); j++) {
			Vecteur3D distanceVect = particuleList[i]->getPosition() - particuleList[j]->getPosition();
			double distanceVal = distanceVect.norm();
			if (distanceVal <= 2 * particuleSize) {
				double penetration = 2 * particuleSize - distanceVal;
				Vecteur3D contactNormal = distanceVect.normalization();
				ParticleContact* particleContact = new ParticleContact(particuleList[i], particuleList[j], particuleRestitution, penetration, contactNormal);
				add(particleContact);
			}
		}
	}
}

void ParticleContactRegistry::checkCableCollision(vector<ParticleCable*> cableList) {
	for (int i = 0; i < cableList.size(); i++) {
		ParticleContact* particleContact = new ParticleContact();
		unsigned numContactsGround = cableList[i]->addContact(particleContact);
		if (numContactsGround == 1) {
			//this means that the distance between the two particles is > maxlenght
			add(particleContact);
		}
	}
}

void ParticleContactRegistry::updateContact(vector<Particule*> particuleList, vector<ParticleCable*> cableList, double particuleSize, double particuleRestitution, double groundHeight, double waterHeight) {
	checkGroundCollision(particuleList, particuleSize, groundHeight, waterHeight);
	checkParticlesCollision(particuleList, particuleSize, particuleRestitution);
	checkCableCollision(cableList);
}