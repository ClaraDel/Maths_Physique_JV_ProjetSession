#include "ParticleContactRegistry.h"

using namespace std;

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
			m_contactList.erase(i);
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

void ParticleContactRegistry::checkWaterCollision(vector<Particule*> particuleList) {

}

void ParticleContactRegistry::checkParticlesCollision(vector<Particule*> particuleList) {

}

void ParticleContactRegistry::checkCableCollision(vector<ParticleCable*> cableList) {

}

void ParticleContactRegistry::updateContact(vector<Particule*> particuleList, vector<ParticleCable*> cableList, , double particuleSize, double groundHeight, double waterHeight) {
	checkGroundCollision(particuleList);
	checkWaterCollision(particuleList);
	checkParticlesCollision(particuleList);
	checkCableCollision(cableList);
}