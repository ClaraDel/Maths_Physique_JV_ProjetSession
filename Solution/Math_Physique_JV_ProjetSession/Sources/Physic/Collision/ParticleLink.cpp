#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vecteur3D length = particule[0]->getPosition() - particule[1]->getPosition();
	return length.norm();
}


