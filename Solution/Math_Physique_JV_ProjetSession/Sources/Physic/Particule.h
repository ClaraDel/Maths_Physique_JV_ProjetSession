#ifndef DEF_PARTICULE
#define DEF_PARTICULE
#include "../Math/Vecteur3D.h"
#include <iostream>
#include<vector>

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
    std::vector<Vecteur3D> tablForces;

    public:
    Particule(double m = 0.0, Vecteur3D pos = Vecteur3D(), Vecteur3D vit = Vecteur3D(), double f =0);
    ~Particule();

    std::vector<Vecteur3D> getTablForces();

	double getInverseMasse() const; 
	void setInverseMasse(double value);

	Vecteur3D getPosition();
	void setPosition(Vecteur3D const& position);
	void setPosition(double const x, double const y, double const z);

	void setAcceleration(double const x, double const y, double const z);
	void setVelocity(double const x, double const y, double const z);
	
	void setMasse(double value);

    //APPLICATION LOIS PHYSIQUES
    void updateVector(Vecteur3D const& vecteurAIntegrer, double temps, Vecteur3D& constanteIntegration);
    void integrate(double temps);
    void addForce(Vecteur3D forceAjout);
    void accelerationCalcul();
	};


#endif