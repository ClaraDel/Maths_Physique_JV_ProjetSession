#include "Particule.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Particule::Particule(double m, Vecteur3D pos, Vecteur3D vit, double d, Vecteur3D rvbC, Vecteur3D form){
	masse = m;
	position = pos;
	velocity = vit;
	acceleration = Vecteur3D();
	damping = d;
	rvbColor = rvbC; //Particule color 
	formSize = form; //vector that contains information about particle's shape 
	forceApplied = Vecteur3D();
	//vector<Vecteur3D> tablForces; //set of forces applied
	/*Vecteur3D gravity= Vecteur3D(0, - 10 * masse, 0); //gravity is applied to all particles
	addForce(gravity);*/
	
	if(m!=0){
		inverseMasse = 1/m;
	} else {
		inverseMasse = 0;
	}
}
Particule::~Particule()
{

}

/*vector<Vecteur3D> Particule::getTablForces()  {
	return tablForces;
}*/

double Particule::getInverseMasse() const{
	return inverseMasse;
}

double Particule::getMasse() const {
	return masse;
}

Vecteur3D Particule::getRVBColor() const {
	return rvbColor;
}

Vecteur3D Particule::getAcceleration() {
	return acceleration;
}

Vecteur3D Particule::getVelocity() {
	return velocity;
}

Vecteur3D Particule::getFormSize() const {
	return formSize;
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

//integrate the chosen vector and update its value
void Particule::updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector){
	vector += deltaTime * integrateVector ;
}

//update of particle's position, acceleration and then velocity
void Particule::integrate(double deltaTime) {
	if (deltaTime > 0) {
		updateVector(velocity, deltaTime, position); //calculates the new position
		accelerationCalcul(); //calculates the new acceleration
		updateVector(acceleration, deltaTime, velocity); //calculates the new velocity
		velocity *= pow(damping, deltaTime);
		
	}
}

//if we want to add some forces to our particle
void Particule::addForce(Vecteur3D forceToAdd) {
	forceApplied += forceToAdd;
}

//Application of Newton's law
void Particule::accelerationCalcul() {
	acceleration = inverseMasse * forceApplied ;
}