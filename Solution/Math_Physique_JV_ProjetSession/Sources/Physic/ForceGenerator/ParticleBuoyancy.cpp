#include"ParticleBuoyancy.h"

void ParticleBuoyancy::UpdateForce(Particule* particule, double duration)
{
	//submersion depth
	double depth = particule->getPosition().getY();
	Vecteur3D force;

	//Are they out of the water ?
	if (depth >= waterHeight + maxDepth) {

	 // are they in the water ?
	}
	else if (depth <= waterHeight - maxDepth) {
		force.setY(liquidDensity * volume);
		particule->addForce(force);
		//partly submerged
	} else {
		force.setY(liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth);
		particule->addForce(force);
	}
}