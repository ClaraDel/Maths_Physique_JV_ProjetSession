#include "ParticleSpring.h"

using namespace std;

ParticleSpring::ParticleSpring(Particule* other, double k, double l0) {
	m_other = other;
	m_k = k;
	m_l0 = l0;
}

void ParticleSpring::UpdateForce(Particule* particule, double duration)
{
	Vecteur3D force;
	Vecteur3D A(particule->getPosition());
	Vecteur3D B(m_other->getPosition());

	//Hooke's Law
	force  = -m_k  * ((A  -  B).norm() - m_l0)  *  (A  -  B).normalization();
	particule->addForce(force);
}