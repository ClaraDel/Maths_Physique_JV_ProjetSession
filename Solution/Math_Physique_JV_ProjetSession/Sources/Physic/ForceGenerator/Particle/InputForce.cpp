#include "InputForce.h"

using namespace std;

InputForce::InputForce(const Vecteur3D& force) {
	m_force = force;
}

void InputForce::changeForceValue(double xValue, double yValue, double zValue) {
	m_force = Vecteur3D(xValue, yValue, zValue);
}

Vecteur3D InputForce::getForce() {
	return m_force;
}

void InputForce::UpdateForce(Particule* particule, double duration)
{
	particule->addForce(particule->getMasse() * m_force);
}