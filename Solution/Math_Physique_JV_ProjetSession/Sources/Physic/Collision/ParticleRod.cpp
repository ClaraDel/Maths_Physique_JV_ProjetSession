#include "ParticleRod.h"

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const
{
	double currentLenght = ParticleLink::currentLenght(); 
	
	if (currentLenght == lenght){
		return 0;

	} else {
		contact->setParticules(particule[0], particule[1]);

		//calculate the normal between these two particle
		Vecteur3D normal = particule[1]->getPosition() - particule[0]->getPosition();
		normal.normalization();

		if (currentLenght > lenght) {
			contact->setContactNormal(normal);
			contact->setPenetration(currentLenght - lenght);
		} else {
			contact->setContactNormal(-1*normal);
			contact->setPenetration(lenght - currentLenght);
		}

		//we don't want boudiness
		contact->setRestitution(0);

		return 1;
	}
}

