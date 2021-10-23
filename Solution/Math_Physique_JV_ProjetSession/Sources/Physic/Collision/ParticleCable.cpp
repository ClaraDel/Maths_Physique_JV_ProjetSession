#include "ParticleCable.h"

ParticleCable::ParticleCable(Particule* p1, Particule* p2, float mLength)
{
	particule[0] = p1;
	particule[1] = p2;
	maxLenght = mLength;
}


unsigned int ParticleCable::addContact(ParticleContact* contact) 
{
	double currentLenght = ParticleLink::currentLenght();

	if (currentLenght < maxLenght) {
		return 0;

	}
	else { 
		Vecteur3D normal = particule[1]->getPosition() - particule[0]->getPosition();
		normal.normalization();
		*contact = ParticleContact(particule[0], particule[1], 0, currentLenght - maxLenght, normal);
		return 1;
	}
}