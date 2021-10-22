#include"ParticleBuoyancy.h"
#include <iostream>

using namespace std;

ParticleBuoyancy::ParticleBuoyancy(float particuleSize, double volume, double waterHeight, double liquidDensity) {
	m_maxDepth = 1- particuleSize ;
	m_particuleSize = particuleSize;
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
		cout << "TOTAL" <<endl;
		cout << force.getY() << endl;
		particule->addForce(force);
	
	//partly submerged
	} else {
			double d = (m_waterHeight - (depth - m_particuleSize))/(2*m_particuleSize)  ;
		double forceY = m_liquidDensity * m_volume * d * 10;
		force.setY(forceY) ;
		cout << "PARTLY" << endl;
		cout << force.getY() << endl; 
		particule->addForce(force);
	}
}