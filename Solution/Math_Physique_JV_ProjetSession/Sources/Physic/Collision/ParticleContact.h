#pragma once
#ifndef DEF_PARTICLECONTACT
#define DEF_PARTICLECONTACT
#include"../Particule.h"

class ParticleContact {

private : 
    //particleContact properties
	Particule* m_particules[2];
	//elasticness of the collision
	double m_restitution;
	// penetration of the contact
	double m_penetration;
	//normal of the contact
	Vecteur3D m_contactNormal;

	//impulse of the collision
	void resolveVelocity();
	// handle interpenetration of the contact 
	void resolveInterpenetration();



public : 
	ParticleContact();
	ParticleContact(Particule* p1, Particule* p2, float restitution = 0, float penetration = 0, Vecteur3D contactNormal = Vecteur3D());

	void setPenetration(double penetration);
	void setRestitution(double restitution);
	void setContactNormal(Vecteur3D cn);
	void setParticules(Particule* p1, Particule* p2);

	//Resolve interpenetration and velocity 
	void resolve();

	//Calculate and return the separtionVelocity  of the particles
	double calculateSeperatingVelocity();

	
};

#endif