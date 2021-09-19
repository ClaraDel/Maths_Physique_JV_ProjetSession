#ifndef DEF_VECTEUR
#define DEF_VECTEUR
#include <math.h>
#include <iostream>

class Vecteur3D {

public:

	Vecteur3D();
	Vecteur3D(double x1,double y1,double z1);

	double norme() const;
	Vecteur3D normalisation() const;
	void baseOrthogonal(Vecteur3D  a, Vecteur3D  b, Vecteur3D c);
	Vecteur3D produitVectoriel(Vecteur3D const& vecteur) const;
	double produitScalaire(Vecteur3D const& vecteur) const;
	Vecteur3D additioner(Vecteur3D const& vecteur) const;
	Vecteur3D soustraire(Vecteur3D const& vecteur) const;
	Vecteur3D multiplier(double value) const;
	Vecteur3D diviser(double value) const;
	bool estEgal(Vecteur3D const& vecteur) const;

	void afficher(ostream &flux) const;

	Vecteur3D& operator+=(Vecteur3D const& vecteur);
	Vecteur3D& operator-=(Vecteur3D const& vecteur);
	Vecteur3D& operator*=(double value);
	Vecteur3D& operator/=(double value);




private:
	double x, y, z;

};

Vecteur3D operator*(double value,Vecteur3D const& vecteur);
Vecteur3D operator/(double value,Vecteur3D const& vecteur);
Vecteur3D operator+(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
Vecteur3D operator-(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
bool operator==(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
bool operator!=(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
std::ostream& operator<< (std::ostream& flux, Vecteur3D const& vecteur);

#endif