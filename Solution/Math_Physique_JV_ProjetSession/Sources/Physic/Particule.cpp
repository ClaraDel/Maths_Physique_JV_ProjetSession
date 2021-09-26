#include "Particule.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Particule::Particule(double m, Vecteur3D pos, Vecteur3D vit, double d, Vecteur3D rvbC, Vecteur3D sphereS){
	masse = m;
	position = pos;
	velocity = vit;
	acceleration = Vecteur3D();
	damping = d;
	rvbColor = rvbC;
	sphereSize = sphereS;
	vector<Vecteur3D> tablForces;
	Vecteur3D gravity= Vecteur3D(0, - 10 * masse, 0);
	addForce(gravity);
	
	if(m!=0){
		inverseMasse = 1/m;
	} else {
		inverseMasse = 0;
	}
}
Particule::~Particule()
{

}

vector<Vecteur3D> Particule::getTablForces()  {
	return tablForces;
}

double Particule::getInverseMasse() const{
	return inverseMasse;
}

Vecteur3D Particule::getRVBColor() const {
	return rvbColor;
}

Vecteur3D Particule::getAcceleration() {
	return acceleration;
}

Vecteur3D Particule::getSphereSize() const {
	return sphereSize;
}

void Particule::setInverseMasse(double value) {
	inverseMasse = value;
}

void Particule::setMasse(double value){
	masse = value;
	if (value!= 0) {
		inverseMasse = 1 / value;
	}
	else {
		inverseMasse = 0;
	}
}

Vecteur3D Particule::getPosition() {
	return position;
}
void Particule::setPosition(Vecteur3D const& p) {
	position = p;
}
void Particule::setPosition(double const x, double const y, double const z) {
	position = Vecteur3D(x, y, z);

}
void Particule::setAcceleration(double const x, double const y, double const z) {
	acceleration = Vecteur3D(x, y, z);
}

void Particule::setVelocity(double const x, double const y, double const z) {
	velocity = Vecteur3D(x, y, z);
}

void Particule::setDamping(double d){
	damping = d;
}

void Particule::updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector){
	vector += deltaTime * integrateVector ;
}
void Particule::integrate(double deltaTime) {
	//acceleration constante en fonction du temps
	if (deltaTime > 0) {
		updateVector(velocity, deltaTime, position);
		accelerationCalcul();
		updateVector(acceleration, deltaTime, velocity);
		velocity *= pow(damping, deltaTime);
	}
}

void Particule::addForce(Vecteur3D forceToAdd) {
	tablForces.push_back(forceToAdd);
}
void Particule::accelerationCalcul() {
	acceleration = inverseMasse * sumVectors(tablForces) ;
}