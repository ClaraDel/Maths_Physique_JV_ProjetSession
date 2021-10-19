#pragma once
#ifndef DEF_PARTICLECONTACT
#define DEF_PARTICLECONTACT
#include"../Particule.h"

class ParticleContact {

private : 
	Particule* m_particules[2];
	double m_restitution;
	double m_penetration;
	Vecteur3D m_contactNormal;

	void resolveVelocity();
	void resolveInterpenetration();


public : 
	ParticleContact();
	ParticleContact(Particule* p1, Particule* p2, float restitution, float penetration, Vecteur3D contactNormal);

	void resolve();
	double calculateSeperatingVelocity();

	
};

#endif