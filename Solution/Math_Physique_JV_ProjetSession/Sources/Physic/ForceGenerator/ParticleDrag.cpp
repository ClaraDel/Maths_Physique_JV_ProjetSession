#include "ParticleDrag.h"

ParticleDrag::ParticleDrag(double k1, double k2) {
	m_k1 = k1;
	m_k2 = k2;
}



void ParticleDrag::UpdateForce(Particule* particule, double duration) {
	Vecteur3D force;
	Vecteur3D pVelocity = particule->getVelocity();
	double pVelocityNorm = pVelocity.norm();
	force = (m_k1 * pVelocityNorm + m_k2 * pVelocityNorm * pVelocityNorm) * -1 * pVelocity.normalization();
	particule->addForce(force);
}