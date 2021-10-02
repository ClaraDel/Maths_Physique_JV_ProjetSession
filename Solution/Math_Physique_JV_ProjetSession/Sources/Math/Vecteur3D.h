#ifndef DEF_VECTEUR
#define DEF_VECTEUR
#include <math.h>
#include <iostream>
#include <vector>

class Vecteur3D {  

public:

	Vecteur3D();
	Vecteur3D(double x1,double y1,double z1);

	double norm() const;
	Vecteur3D normalization() const;
	void orthogonalBase(Vecteur3D  a, Vecteur3D  b, Vecteur3D c);
	Vecteur3D vectorProduct(Vecteur3D const& vecteur) const;
	double scalarProduct(Vecteur3D const& vecteur) const;
	Vecteur3D add(Vecteur3D const& vecteur) const;
	Vecteur3D substract(Vecteur3D const& vecteur) const;
	Vecteur3D multiply(double value) const;
	Vecteur3D divide(double value) const;
	bool isEqual(Vecteur3D const& vecteur) const;

	void print(std::ostream& flux) const;

	double getX() const;
	double getY() const;
	double getZ() const;
	void setX(double value);
	void setY(double value) ;
	void setZ(double value) ;

	Vecteur3D& operator+=(Vecteur3D const& vecteur);
	Vecteur3D& operator-=(Vecteur3D const& vecteur);
	Vecteur3D& operator*=(double value);
	Vecteur3D& operator/=(double value);




private:
	double x, y, z;

};

//SOMME TABLEAU VECTEURS ###
Vecteur3D sumVectors(std::vector<Vecteur3D> const& tablForces);

//OPERATEURS ###
Vecteur3D operator*(double value,Vecteur3D const& vecteur);
Vecteur3D operator/(double value,Vecteur3D const& vecteur);
Vecteur3D operator+(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
Vecteur3D operator-(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
bool operator==(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
bool operator!=(Vecteur3D const& vecteur1,Vecteur3D const& vecteur2);
std::ostream& operator<< (std::ostream& flux, Vecteur3D const& vecteur);

#endif