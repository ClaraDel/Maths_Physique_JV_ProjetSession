#pragma once
#ifndef DEF_PARTICULEANCHOREDSPRING
#define DEF_PARTICULEANCHOREDSPRING
#include"../Particule.h"
#include"ParticleForceGenerator.h"

/*Apply a spring force where one end is attached
to a fixed point in space*/

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
	//anchor
	Vecteur3D* m_anchor;
	//Spring constant
	double m_k;
	double m_l0;

public:
	ParticleAnchoredSpring(Vecteur3D* anchor, double k, double l0);
	//apply Hooke's law based on particles position
	void UpdateForce(Particule* particle, double duration);
};

#endif