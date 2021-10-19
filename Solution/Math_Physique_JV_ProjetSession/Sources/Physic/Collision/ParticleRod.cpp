#include "ParticleRod.cpp"

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const
{
	double currentLenght = currentLenght(); 

	if (currentLenght = lenght){
		return 0;

	} else {
		contact->particle[0] = particle[0]; 
		contact->particle[1] = particle[1];

		//calculate the normal between these two particle
		Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
		normal.normalize();

		if (currentLenght > lenght) {
			contact->contactNormal = normal;
			contact->penetration = currentLenght - lenght;
		} else {
			contact->contactNormal = normal * -1;
			contact->penetration = lenght - currentLenght ;
		}

		//we don't want boudiness
		contact->restitution = 0;

		return 1;
	}


