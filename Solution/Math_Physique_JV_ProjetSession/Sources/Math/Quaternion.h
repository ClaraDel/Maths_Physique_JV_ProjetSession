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
	Quaternion(double w, double x, double y, double z);
	//Calculate his norm
	double norm() const;
	double getW() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	//normalize the quaternion by multipling it with the inverse of his norm
	void normalize();
	//Rotate the quaternion by a vector 
	void rotateByVector(const Vecteur3D& vecteur);
	//update the quaternion with angular velocity
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