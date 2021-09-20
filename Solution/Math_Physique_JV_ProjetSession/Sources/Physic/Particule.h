#ifndef DEF_PARTICULE
#define DEF_PARTICULE
#include "Vecteur3D.h"

#pragma once

class Particule
{
    private :
    double masse;
    double inverseMasse; 
	double damping;
    Vecteur3D position;
    Vecteur3D positionInitiale;
    Vecteur3D velocity;
    Vecteur3D initialVelocity;
    Vecteur3D acceleration;
    Vecteur3D accelerationInitiale;
    vector<Vecteur3D> tablForces();

    public:
    Particule(double m = 0.0, Vecteur3D pos = Vecteur3D(), Vecteur3D vit = Vecteur3D(), double f =0);
    ~Particule();
	double getInverseMasse() const; 
	void setInverseMasse(double value);
	void setMasse(double value);

    //APPLICATION LOIS PHYSIQUES
    Vecteur3D miseAJourVecteur(Vecteur3D const& vecteurAIntegrer, double temps, Vecteur3D const& constanteIntegration);
    void integrate(double temps);
    void ajoutForce(Vecteur3D forceAjout);
    void calculAcceleration();
	};


#endif