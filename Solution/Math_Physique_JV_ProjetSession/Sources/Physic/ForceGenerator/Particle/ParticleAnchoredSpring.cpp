#include"ParticleAnchoredSpring.h"

using namespace std;

ParticleAnchoredSpring::ParticleAnchoredSpring(Vecteur3D *anchor, double k, double l0) {
	m_anchor = anchor;
	m_k = k;
	m_l0 = l0;
}

void ParticleAnchoredSpring::UpdateForce(Particule* particule, double duration)
{
	Vecteur3D force;
	Vecteur3D A(particule->getPosition());
	Vecteur3D B(*m_anchor);

	force  = -m_k  * ((A  -  B).norm() - m_l0)  *  (A  -  B).normalization();
	particule->addForce(force);

}