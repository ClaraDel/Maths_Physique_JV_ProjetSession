#include"ParticleBuoyancy.h"
#include <iostream>

using namespace std;

ParticleBuoyancy::ParticleBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity) {
	m_maxDepth = maxDepth;
	m_waterHeight = waterHeight;
	m_volume = volume;
	m_liquidDensity = liquidDensity;
}

void ParticleBuoyancy::UpdateForce(Particule* particule, double duration)
{
	//submersion depth
	double depth = particule->getPosition().getY();
	Vecteur3D force;

	//Are they out of the water ?
	if (depth >= m_waterHeight + m_maxDepth) {
		return;
	 // are they in the water ?
	}
	else if (depth <=  m_maxDepth) {
		force.setY(m_liquidDensity * m_volume * 10);
		cout << "CAS 1" <<endl;
		particule->addForce(force);
	
	//partly submerged
	} else {
		force.setY(m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth* 10) ;
		cout << "CAS 2" << endl; //PROBLEME ICI 
		particule->addForce(Vecteur3D(0,400,0));
	}
}