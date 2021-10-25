#ifndef DEF_MATRIX34
#define DEF_MATRIX34
#include "Matrix33.h"

class Matrix34 {

private :
	float values[12];


public :

	Matrix34& operator+=(const Matrix34& other);
	Matrix34& operator-=(const Matrix34& other);
	Matrix34& operator*=(double value);
	Matrix34& operator*=(const Matrix34& other);

	double getValue(int i) const;
	void setValue(int i, double v);

	Matrix34& identity();

	//combination of affine transformation
	Matrix34 operator*(const Matrix34& other) const;

	//transform of a vector
	Vecteur3D operator*(const Vecteur3D& vecteur) const;

	//get the determinant 
	double Det();
	//get the inverse matrix
	Matrix34 Inverse();

	//Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vecteur3D& p);

	Vecteur3D localToWorld(const Vecteur3D &local,  Matrix34 &transform);
	
	Vecteur3D  worldToLocal(const Vecteur3D &local,  Matrix34 &transform);

	//transform a position
	Vecteur3D TransformPosition(const Vecteur3D& vector);

	//Transform a direction by ignoring the translation
	Vecteur3D TransformDirection(const Vecteur3D& vector);
}; 

#endif

