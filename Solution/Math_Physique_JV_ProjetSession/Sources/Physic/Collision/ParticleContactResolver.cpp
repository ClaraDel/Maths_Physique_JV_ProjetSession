#include"ParticleContactResolver.h"

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration) {

	unsigned i;
	unsigned maxIndex = numContacts;

	int interationUsed = 0;
	double maxSepVel = contactArray[0].calculateSeperatingVelocity();

	while(iterationUsed < nbIterations) {
		
		for (i = 1; i < numContact, i++) {
			double separatingVelocity = contactArray[i].calculateSeperatingVelocity();
			if (separatingVelocity < maxSepVel && (separatingVelocity < 0) //ou pénétration positive à voir
			{
				maxSepVel = separatingVelocity
				maxIndex = i;
			}
		}

		//if(maxIndex == numContacts) break ;

		//resolve the contact
		contactArray[maxIndex].resolve(duration);
		
		interationUsed++;
		
	}

}