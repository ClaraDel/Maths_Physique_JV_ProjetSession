#include "Vecteur3D.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;  

Vecteur3D::Vecteur3D():x(0.0),y(0.0),z(0.0){}

Vecteur3D::Vecteur3D(double x1,double y1,double z1):x(x1),y(y1),z(z1){}

//to get the norm of our vector
double Vecteur3D::norm() const 
{
	double n(0.0);
	n = sqrt((pow(x,2)+pow(y,2)+pow(z,2)));
	return n;
}

//to normalize our vector
Vecteur3D Vecteur3D::normalization() const
{
	double n(this->norm());
	Vecteur3D resultat(x,y,z);
	resultat /= n;
	return resultat;
}

//create an orthogonal base with three vectors a, b and c
void Vecteur3D::orthogonalBase(Vecteur3D  a, Vecteur3D b, Vecteur3D c)
{
	a = a.normalization();
	c = a.vectorProduct(b);
	if (c != Vecteur3D(0, 0, 0))
	{
		c = c.normalization();
		b = c.vectorProduct(a);
	}
	else
		return;

}

//vector product between this vector and another one, the result is stored in a third vector
Vecteur3D Vecteur3D::vectorProduct(Vecteur3D const& vector) const
{
	Vecteur3D resultat(0,0,0);
	resultat.x = y*vector.z - z *vector.y;
	resultat.y = z * vector.x - x * vector.z;
	resultat.z = x*vector.y - y*vector.x;
	return resultat;
}


//scalar product between this vector and another one, the result is stored in a third vector
double Vecteur3D::scalarProduct(Vecteur3D const& vector) const
{
	double ps(0.0);
	ps = x*vector.x + y*vector.y +z*vector.z;
	return ps;
}


//the sum of this vector and another one, the result is stored in a third vector
Vecteur3D Vecteur3D::add(Vecteur3D const& vector) const{
	Vecteur3D resultat(x + vector.x, y + vector.y, z + vector.z);
	return resultat;
}

//the substraction this vector and another one, the result is stored in a third vector
Vecteur3D Vecteur3D::substract(Vecteur3D const& vector) const{
	Vecteur3D resultat(x - vector.x, y - vector.y, z - vector.z);
	return resultat;
}

//the multiplication of this vector by a scalar, the result is stored in antoher vector
Vecteur3D Vecteur3D::multiply(double value) const{
	Vecteur3D resultat(x*value, y*value, z*value);
	return resultat;
}

//the division of this vector by a scalar, the result is stored in antoher vector
Vecteur3D Vecteur3D::divide(double value) const{
	if(value != 0.0) {
		Vecteur3D result(x/value, y/value, z/value);
		return result;
	} else {
		cout << "You can't divide by 0";
		return *this;
	}
}

//we check if this vector and another one are equal
bool Vecteur3D::isEqual(Vecteur3D const& vector) const
{
	if ( x == vector.x  && y == vector.y && z == vector.z) {
		return true;
	} else {
		return false;
	}
}


//we print each element of the vector like this (x, y, z)
void Vecteur3D::print(ostream& flux) const
{
	flux << "(" << x << "," << y << "," << z << ")";
}


//the sum this vector and another one, the result is stored in the first one
Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

//the substraction this vector and another one, the result is stored in the first one
Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}


//the multiplication of this vector by a scalar, the result is stored in the vector
Vecteur3D& Vecteur3D::operator*=(double value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

//the division of this vector by a scalar, the result is stored in the vector
Vecteur3D& Vecteur3D::operator/=(double value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}


//to get the first element of the vector
double Vecteur3D::getX() const {
	return x;
}

//to get the two element of the vector
double Vecteur3D::getY() const {
	return y;
}

//to get the third element of the vector
double Vecteur3D::getZ() const {
	return z;
}

//to sum more than two vectors stored in a table
Vecteur3D sumVectors(vector<Vecteur3D> const& tablForces) {
	Vecteur3D sum;
	for (int i(0); i < tablForces.size(); i++) {
		sum += tablForces[i];
	}
	return sum;
}

//OPERATORS ######
Vecteur3D operator+(Vecteur3D const& a,Vecteur3D const& b)
{
	Vecteur3D result;
	result = a.add(b);
	return result;
}

Vecteur3D operator-(Vecteur3D const& a,Vecteur3D const& b)
{
	Vecteur3D result;
	result = a.substract(b);
	return result;
}

Vecteur3D operator*(double value, Vecteur3D const& a)
{
	Vecteur3D result;
	result = a.multiply(value);
	return result;
}

Vecteur3D operator/(double value,Vecteur3D const& a)
{
	Vecteur3D result;
	result = a.divide(value);
	return result;
}

bool operator==(Vecteur3D const& a,Vecteur3D const& b)
{
	return a.isEqual(b);
}

bool operator!=(Vecteur3D const& a,Vecteur3D const& b)
{
	if (a == b) 
		return false;
	else
		return true;
}

//print a message
std::ostream& operator<< (std::ostream& flux, Vecteur3D const& vecteur)
{
	vecteur.print(flux);
	return flux;
}
