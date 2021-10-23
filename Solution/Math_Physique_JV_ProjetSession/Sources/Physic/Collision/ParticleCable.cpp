#include "ParticleCable.h"

ParticleCable::ParticleCable(Particule* p1, Particule* p2, float mLength)
{
	particule[0] = p1;
	particule[1] = p2;
	maxLenght = mLength;
}

unsigned int ParticleCable::addContact(ParticleContact* contact, unsigned int limit) const
{
	double currentLenght = ParticleLink::currentLenght();

	if (currentLenght < maxLenght) {
		return 0;

	}
	else { 
		contact->setParticules(particule[0], particule[1]);

		Vecteur3D normal = particule[1]->getPosition() - particule[0]->getPosition();
		normal.normalization();
		contact->setContactNormal(normal);

		contact->setPenetration(currentLenght - maxLenght);
		contact->setRestitution(0);

		return 1;
	}
}