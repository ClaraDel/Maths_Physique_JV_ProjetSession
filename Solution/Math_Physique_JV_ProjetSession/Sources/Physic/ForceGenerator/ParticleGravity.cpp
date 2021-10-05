#include "ParticleGravity.h"

using namespace std;

ParticleGravity::ParticleGravity() {
	m_gravity = Vecteur3D(0, -10, 0);
}

void ParticleGravity::UpdateForce(Particule* particule, double duration)
{	
	//we check if the particle does not have infinite mass
	if (particule->getMasse() == 0) return;
	particule->addForce(particule->getMasse() * m_gravity);
}