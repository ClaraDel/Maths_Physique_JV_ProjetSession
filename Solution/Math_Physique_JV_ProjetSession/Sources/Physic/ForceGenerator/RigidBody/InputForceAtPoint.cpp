#include "InputForceAtPoint.h"

using namespace std;

InputForceAtPoint::InputForceAtPoint(Vecteur3D force, Vecteur3D pointPos) {
	m_launch = true;
	m_force = force;
	m_pos = pointPos;
}

void InputForceAtPoint::UpdateForce(RigidBody* rigidBody, double duration)
{
	if (m_launch == true) {
		rigidBody->addForceAtBodyPoint((1.0/duration) * m_force , m_pos);
		m_launch = false; 
	}
}

