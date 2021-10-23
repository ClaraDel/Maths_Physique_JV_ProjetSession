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
	ParticleContact(Particule* p1, Particule* p2, float restitution = 0, float penetration = 0, Vecteur3D contactNormal = Vecteur3D());

	void setPenetration(double penetration);
	void setRestitution(double restitution);
	void setContactNormal(Vecteur3D cn);
	void setParticules(Particule* p1, Particule* p2);
	void resolve();
	double calculateSeperatingVelocity();

	
};

#endif