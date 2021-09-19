#include "Particule.h"
#include <iostream>
#include <string>


using namespace std;

Particule::Particule(double m, Vecteur3D pos, Vecteur3D vit){
	masse = m;
	position = pos;
	positionInitiale = pos;
	vitesse = vit;
	vitesseInitiale = vit;
	acceleration = Vecteur3D acc();
	
	if(m!=0){
		inverseMasse = 1/m;
	} else {
		inverseMasse = 0;
		cout << "Masse de la particule nulle";
	}
}

double Particule::getInverseMasse() const{
	return inverseMasse;
}

void Particule::setInverseMasse(double value) {
	inverseMasse = value;
}

Vecteur3D Particule::integrationVecteur(Vecteur3D const& vecteurAIntegrer, double temps, Vecteur3D const& constanteIntegration){
	Vecteur3D resultat;	
	resultat = vecteurAIntegrer * temps + constanteIntegration;
	return resultat;
}
void Particule::integrationVecteur(double temps) {
	//acceleration constante en fonction du temps
	if (temps > 0) {
		acceleration = calculAcceleration();
		vitesse = miseAJourVecteur(acceleration, temps, vitesseInitiale);
		position = miseAjourVecteur(vitesse, temps, positionInitiale);
		/*vitesse = acceleration * temps * inverseMasse + vitesseInitiale;
		position = 0.5 * pow(temps,2) * acceleration * inverseMasse + vitesseInitiale * temps + positionInitiale;*/
	}

void Particule::ajoutForce(Vecteur3D forceAjout) {
	forces.push_back(forceAjout);
}

void Particule::calculAcceleration() {
	//forces
	//A FAIRE
}