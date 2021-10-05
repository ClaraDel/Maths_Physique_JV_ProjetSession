#include "ConstantForce.h"

using namespace std;


ConstantForce::ConstantForce(const Vecteur3D& force) {
	m_force = force;
}

void ConstantForce::UpdateForce(Particule* particule, double duration)
{
	particule->addForce(particule->getMasse() * m_force);
}