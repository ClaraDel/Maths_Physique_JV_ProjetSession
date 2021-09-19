#include "Vecteur3D.h"
#include <iostream>
#include <string>

using namespace std;

Vecteur3D::Vecteur3D():x(0.0),y(0.0),z(0.0){}

Vecteur3D::Vecteur3D(double x1,double y1,double z1):x(x1),y(y1),z(z1){}

 
double Vecteur3D::norme() const 
{
	double n(0.0);
	n = sqrt(pow(x,2),pow(y,2),pow(z,2));
	return n;
}

Vecteur3D Vecteur3D::normalisation() const
{
	double n(this->norme());
	Vecteur3D resultat(x,y,z);
	resultat /=d;
	return resultat;


}

Vecteur3D Vecteur3D::produitVectoriel(Vecteur3D const& vecteur) const
{
	Vecteur3D resultat(0,0,0);
	resultat.x = y*vecteur.z - z *b.y;
	resultat.y = = z * vecteur.x - x * vecteur.z;
	resultat.z = x*vecteur.y - y*vecteur.x;
	return resultat;
}
double Vecteur3D::produitScalaire(Vecteur3D const& vecteur) const
{
	double ps(0.0);
	ps = x*vecteur.x + y*vecteur.y +e*vecteur.z;
	return ps;
}

Vecteur3D Vecteur3D::additioner(Vecteur3D const& vecteur) const{
	Vecteur3D resultat(x + vecteur.x, y + vecteur.y, z + vecteur.z);
	return resultat;
}

Vecteur3D Vecteur3D::soustraire(Vecteur3D const& vecteur) const{
	Vecteur3D resultat(x - vecteur.x, y - vecteur.y, z - vecteur.z);
	return resultat;
}

Vecteur3D Vecteur3D::multiplier(double value) const{
	Vecteur3D resultat(x*value, y*value, z*value);
	return value;
}

Vecteur3D Vecteur3D::diviser(double value) const{
	if(value != 0) {
		Vecteur3D resultat(x/value, y/value, z/value);
		return resultat;
	} else {
	cout << "Impossible de diviser par 0";
		return this;
	}
}

void Vecteur3D::afficher(ostream& flux) const
{
	flux << "(" << x << "," << y << "," << z << ")";
}

Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& vecteur)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& vecteur)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

Vecteur3D& Vecteur3D::operator*=(double value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vecteur3D& Vecteur3D::operator/=(double value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}


//OPERATEURS ######
Vecteur3D Vecteur3D::operator+(Vecteur3D const& a,Vecteur3D const& b)
{
	Vecteur3D resultat;
	resultat = a.addition(b);
	return resultat;
}

Vecteur3D 