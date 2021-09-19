#ifndef DEF_PARTICULE
#define DEF_PARTICULE
#include "Vecteur3D.h"

#pragma once

class Particule
{
    private :
    double masse;
    double inverseMasse; 
	double f;
    Vecteur3D position;
    Vecteur3D positionInitiale;
    Vecteur3D vitesse;
    Vecteur3D vitesseInitiale;
    Vecteur3D acceleration;
    Vecteur3D accelerationInitiale;
    vector<Vecteur3D> forces();

    public:
    Particule(double m = 0.0, Vecteur3D pos = Vecteur3D(), Vecteur3D vit = Vecteur3D(), double f =0);
    double getInverseMasse() const; 
	void setInverseMasse(double value);
    void integrateur(double temps);

	
};

#endif