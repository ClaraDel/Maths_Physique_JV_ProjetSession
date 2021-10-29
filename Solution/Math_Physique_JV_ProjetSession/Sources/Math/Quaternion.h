#ifndef DEF_QUATERNION
#define DEF_QUATERNION
#pragma once
#include "Vecteur3D.h"

class Quaternion
{
private:
	//w,x,y,z
	double value[4];

public:
	Quaternion();
	Quaternion(double x, double y, double z, double w);
	double norm() const;
	double getW() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	void normalize();
	void rotateByVector(const Vecteur3D& vecteur);
	void updateByAngularVelocity(const Vecteur3D& rotation, double duration);

	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(double value);
};


//OPERATEURS ###
Quaternion operator*(Quaternion const& quaternion1, Quaternion const& quaternion2);
Quaternion operator+(Quaternion const& q1, Quaternion const& q2);
Quaternion operator-(Quaternion const& q1, Quaternion const& q2);


#endif