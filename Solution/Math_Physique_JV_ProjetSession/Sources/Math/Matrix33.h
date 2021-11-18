#ifndef DEF_MATRIX33
#define DEF_MATRIX33
#include "Vecteur3D.h"
#include "Quaternion.h"
#include<iostream>

class Matrix33
{
private:
	double values[9];
public:
	Matrix33();
	Matrix33(double a, double b, double c, double d, double e, double f, double g, double h, double i);
	//Calculate the determinant of the Matrix 
	double Det();
	//Calculate the Inverse Matrix 
	Matrix33 Inverse();
	//Calculate the Transpose Matrix
	Matrix33 Transpose();
	//Set the matrix base on a Quaternion
	void SetOrientation(const Quaternion& q);
	
	double getValue(int i) const;
	void setValue(int i, double v);

	Matrix33& operator+=(const Matrix33& other);
	Matrix33& operator-=(const Matrix33& other);
	Matrix33& operator*=(const Matrix33& other);
	Matrix33& operator*=(const Vecteur3D& other);
	Matrix33& operator*=(double value);
	//Print the Matrix 
	void print(std::ostream& flux) const;
};

//OPERATEURS ###
Vecteur3D operator*(Matrix33 const& matrix,Vecteur3D const& vecteur );
Matrix33 operator*(double value, Matrix33 const& matrix);
Matrix33 operator*(Matrix33 const& matrix1, Matrix33 const& matrix2);
Matrix33 operator+(Matrix33 const& m1, Matrix33 const& m2);
Matrix33 operator-(Matrix33 const& m1, Matrix33 const& m2);
std::ostream& operator<< (std::ostream& flux, Matrix33 const& matrix);

#endif
