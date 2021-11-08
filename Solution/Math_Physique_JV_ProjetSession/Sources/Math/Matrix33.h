#ifndef DEF_MATRIX33
#define DEF_MATRIX33
#include "Vecteur3D.h"
#include "Quaternion.h"
class Matrix33
{
private:
	double values[9];
public:
	Matrix33();
	Matrix33(double a, double b, double c, double d, double e, double f, double g, double h, double i);
	double Det();
	Matrix33 Inverse();
	Matrix33 Transpose();
	void SetOrientation(const Quaternion& q);
	
	double getValue(int i) const;
	void setValue(int i, double v);

	Matrix33& operator+=(const Matrix33& other);
	Matrix33& operator-=(const Matrix33& other);
	Matrix33& operator*=(const Matrix33& other);
	Matrix33& operator*=(const Vecteur3D& other);
	Matrix33& operator*=(double value);
};

//OPERATEURS ###
Vecteur3D operator*(Matrix33 const& matrix,Vecteur3D const& vecteur );
Matrix33 operator*(double value, Matrix33 const& matrix);
Matrix33 operator*(Matrix33 const& matrix1, Matrix33 const& matrix2);
Matrix33 operator+(Matrix33 const& m1, Matrix33 const& m2);
Matrix33 operator-(Matrix33 const& m1, Matrix33 const& m2);

#endif
