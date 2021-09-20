#include "Particule.h"
#include <iostream>
#include <string>
#include <cmath>


using namespace std;

Particule::Particule(double m, Vecteur3D pos, Vecteur3D vit, double d){
	masse = m;
	position = pos;
	positionInitiale = pos;
	velocity = vit;
	initialVelocity = vit;
	acceleration = Vecteur3D acc();
	dampling = d;
	
	if(m!=0){
		inverseMasse = 1/m;
	} else {
		inverseMasse = 0;
		cout << "Masse de la particule nulle";
	}
}
Particule::~Particule()
{

}

double Particule::getInverseMasse() const{
	return inverseMasse;
}

void Particule::setInverseMasse(double value) {
	inverseMasse = value;
}

void Particule::setMasse(double value){
	masse = value;
}

Vecteur3D Particule::getPosition() 
{
	return position;
}

Vecteur3D& Particule::miseAJourVecteur(Vecteur3D const& vecteurAIntegrer, double temps, Vecteur3D const& constanteIntegration){
	constanteIntegration = vecteurAIntegrer * temps + constanteIntegration;
	return constanteIntegration;
}
void Particule::integrate(double temps) {
	//acceleration constante en fonction du temps
	if (temps > 0) {
		position = miseAjourVecteur(vitesse, temps, position);
		calculAcceleration();
		vitesse = miseAJourVecteur(acceleration, temps, vitesse);
		vitesse *= pow(damping, temps);
		
		/*vitesse = acceleration * temps * inverseMasse + vitesseInitiale;
		position = 0.5 * pow(temps,2) * acceleration * inverseMasse + vitesseInitiale * temps + positionInitiale;*/
	}

void Particule::ajoutForce(Vecteur3D forceAjout) {
	tablForces.push_back(forceAjout);
}

void Particule::calculAcceleration() {
	acceleration = inverseMasse * sommeVecteurs(tablForces) ;
}