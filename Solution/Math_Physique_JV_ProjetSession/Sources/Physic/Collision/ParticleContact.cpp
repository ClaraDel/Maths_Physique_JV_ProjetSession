#include "ParticleContact.h"


ParticleContact::ParticleContact(){
	m_particules[0] = nullptr;
	m_particules[1] = nullptr;
	m_restitution = 0;
	m_penetration = 0;
	m_contactNormal = Vecteur3D();
}

ParticleContact::ParticleContact(Particule* p1, Particule* p2, float restitution, float penetration, Vecteur3D contactNormal) {
	m_particules[0] = p1;
	m_particules[1] = p2;
	m_restitution = restitution;
	m_penetration = penetration;
	m_contactNormal = contactNormal;
}

double ParticleContact::calculateSeperatingVelocity() {
	if (m_particules[1] == nullptr) {
		return m_particules[0]->getVelocity().scalarProduct(m_contactNormal);
	}
	else {
		return (m_particules[0]->getVelocity() - m_particules[1]->getVelocity() ).scalarProduct(m_contactNormal);
	}
}

void ParticleContact::resolve(double duration) {
	resolveVelocity(duration);
	resolveInterpenetration();
}

void  ParticleContact::resolveVelocity() {

}

void  ParticleContact::resolveInterpenetration() {
	if (m_penetration <= 0) return;

	float sumInverseMass = m_particules[0]->getInverseMasse() + m_particules[1]->getInverseMasse();

	Vecteur3D particuleMovement[2];
	particuleMovement[0] = m_particules[1]->getMasse() * m_penetration * sumInverseMass * m_contactNormal;
	particuleMovement[1] = - m_particules[0]->getMasse() * m_penetration * sumInverseMass * m_contactNormal;

	m_particules[0]->setPosition(m_particules[0]->getPosition() + particuleMovement[0]);
	m_particules[1]->setPosition(m_particules[1]->getPosition() + particuleMovement[1]);
}