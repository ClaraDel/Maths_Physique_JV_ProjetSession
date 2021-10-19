#include "ParticleCable.h"

unsigned addContact(ParticleContact* contact, unsigned int limit) const
{
	float length = currentLength();
	if (length < maxLength)
	{
		return 0;
	}
	else {
		contact->m_particule[0] = particule[0];
		contact->m_particule[1] = particule[1];

		Vecteur3D normal = particule[1]->getPosition() - particule[0]->getPosition();
		normal.normalization();
		contact->contactNormal = normal;

		contact->m_penetration = length - maxLength;
		contact->m_restitution = restitution;

		return 1;
	}
}