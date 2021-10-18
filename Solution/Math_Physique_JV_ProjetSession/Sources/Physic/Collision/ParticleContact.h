#pragma once
#ifndef DEF_PARTICLECONTACT
#define DEF_PARTICLECONTACT
#include"../Particule.h"

class ParticleContact {

private : 
	Particule* m_particules[2];
	float m_restituion;
	float m_penetration;
	Vecteur3D m_contactNormal;



public : 
	ParticleContact();
	ParticleContact(Particule p1, Particule p2, float restitution, float penetration, Vecteur3D contactNormal);

	void resolve(float duration);
	void resolveVelocity();
	void resolveInterpenetration();
	float calculateSeperatingVelocity();

};

#endif