#include "ParticleContact.h"


ParticleContact::ParticleContact(){
	m_particules[0] = nullptr; 
	m_particules[1] = nullptr;
	m_restitution = 0; //restitution coefficient
	m_penetration = 0; //distance of penetration between the two particle
	m_contactNormal = Vecteur3D();
}

ParticleContact::ParticleContact(Particule* p1, Particule* p2, float restitution, float penetration, Vecteur3D contactNormal) {
	m_particules[0] = p1;
	m_particules[1] = p2;
	m_restitution = restitution;
	m_penetration = penetration;
	m_contactNormal = contactNormal;
}

//calculate the separating velocity
double ParticleContact::calculateSeperatingVelocity() {
	if (m_particules[1] == nullptr) {
		return m_particules[0]->getVelocity().scalarProduct(m_contactNormal);
	}
	else {
		return (m_particules[0]->getVelocity() - m_particules[1]->getVelocity() ).scalarProduct(m_contactNormal);
	}
}

//Resolve interpenetration and velocity 
void ParticleContact::resolve() {
	resolveVelocity();
	resolveInterpenetration();
}

void ParticleContact::setParticules(Particule* p1, Particule* p2) {
	m_particules[0] = p1;
	m_particules[1] = p2;
}

void ParticleContact::setContactNormal(Vecteur3D cn) {
	m_contactNormal = cn;
}

void ParticleContact::setRestitution(double restitution) {
	m_restitution = restitution;
}

void ParticleContact::setPenetration(double penetration) {
	m_penetration = penetration;
}

//calculate and apply the new velocity of the two particle
void  ParticleContact::resolveVelocity() {
	double separatingVelocity = calculateSeperatingVelocity();

	//check if it needs to be resolved
	if (separatingVelocity > 0) {
		return; 
	}

	//apply the restitution coefficient
	double newSV = -separatingVelocity * m_restitution;

	Vecteur3D vRel = m_particules[0]->getVelocity();
	double inverseMasseParticule1 = 0;

	//if particle is not the ground
	if (m_particules[1] != nullptr) {
		vRel -= m_particules[1]->getVelocity();
		inverseMasseParticule1 = m_particules[1]->getInverseMasse();
	}

	// 1/m0 + 1/m1 if m1 exists
	double coeffInvertMass = m_particules[0]->getInverseMasse() + inverseMasseParticule1;

	//calculate the coefficient k required to calculate the impulse
	double k = (m_restitution + 1) * vRel.scalarProduct(m_contactNormal) / coeffInvertMass;

	//we calcule new velocity for each particle
	m_particules[0]->setVelocity(m_particules[0]->getVelocity() - k * m_particules[0]->getInverseMasse() * m_contactNormal);
	if (m_particules[1] != nullptr) {
		m_particules[1]->setVelocity(m_particules[1]->getVelocity() + k * m_particules[1]->getInverseMasse() * m_contactNormal);
	}
}

//resolve the interpenetration
void  ParticleContact::resolveInterpenetration() {
	if (m_penetration <= 0) return; //there is no interpenetration

	float sumInverseMass = m_particules[0]->getInverseMasse();

	if (m_particules[1] != nullptr) {
		//if penetration occurs with two particle
		// 1/m0 + 1/m1 if m1 exists
		sumInverseMass += m_particules[1]->getInverseMasse();
		if(sumInverseMass <=0 ) return;

		Vecteur3D particuleMovement[2];
		// calculate the distance of displacement required to resolve interpenetration
		particuleMovement[0] = m_particules[0]->getInverseMasse() * (m_penetration / sumInverseMass) * m_contactNormal;
		particuleMovement[1] = - m_particules[1]->getInverseMasse() * (m_penetration /sumInverseMass) * m_contactNormal;

		//update the positions of particles
		m_particules[0]->setPosition(m_particules[0]->getPosition() + particuleMovement[0]);
		m_particules[1]->setPosition(m_particules[1]->getPosition() + particuleMovement[1]);
	}
	else {
		//if penetration occurs with the ground
		m_particules[0]->setPosition(m_particules[0]->getPosition() +  m_penetration  * m_contactNormal);
	}
	
}