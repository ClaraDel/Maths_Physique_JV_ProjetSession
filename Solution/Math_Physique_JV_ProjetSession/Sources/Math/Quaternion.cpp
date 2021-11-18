#include "Quaternion.h"


Quaternion::Quaternion() {
	value[0] = (0, 0);
	value[1] = (0, 0);
	value[2] = (0, 0);
	value[3] = (0, 0);
}
Quaternion::Quaternion(double w,double x, double y, double z)
{
	value[0] = w;
	value[1] = x;
	value[2] = y;
	value[3] = z;
	
}
//His norm
double Quaternion::norm() const
{
	double n(0.0);
	n = sqrt((pow(value[0], 2) + pow(value[1], 2) + pow(value[2], 2) + pow(value[3], 2)));
	return n;
}
//normalize the quaternion by multipling it with the inverse of his norm
void Quaternion::normalize() {
	double n(this->norm());
	if (n == 0) {
		value[0] = 1;
		return;
	}
	value[0] *= (1 / n);
	value[1] *= (1 / n);
	value[2] *= (1 / n);
	value[3] *= (1 / n);

}

double Quaternion::getW() const {
	return value[0];
}

double Quaternion::getX() const {
	return value[1];
}

double Quaternion::getY() const {
	return value[2];
}

double Quaternion::getZ() const {
	return value[3]; 
}

//Rotate the quaternion by a vector 
void Quaternion::rotateByVector(const Vecteur3D& vecteur) {
	Quaternion q(0, vecteur.getX(), vecteur.getY(), vecteur.getZ());
	(*this) *= q;

}
//update the quaternion with angular velocity
void Quaternion::updateByAngularVelocity(const Vecteur3D& rotation, double duration) {
	Quaternion q(0, rotation.getX(), rotation.getY(), rotation.getZ());
	q *= duration;
	q *= *this;
	q *= 1.5;
}

Quaternion& Quaternion::operator*=(double scaler) {
	value[0] *= scaler;
	value[1] *= scaler;
	value[2] *= scaler;
	value[3] *= scaler;
	return *this;

}
Quaternion& Quaternion::operator+=(const Quaternion& other) {
	value[0] += other.value[0];
	value[1] += other.value[1];
	value[2] += other.value[2];
	value[3] += other.value[3];
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other) {
	value[0] -= other.value[0];
	value[1] -= other.value[1];
	value[2] -= other.value[2];
	value[3] -= other.value[3];
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
	value[0] = value[0] * other.value[0] - value[1] * other.value[1] - value[2] * other.value[2] - value[3] * other.value[3];
	value[1] = value[0] * other.value[1] + value[1] * other.value[0] + value[2] * other.value[3] - value[3] * other.value[2];
	value[2] = value[0] * other.value[2] + value[2] * other.value[0] + value[3] * other.value[1] - value[1] * other.value[3];
	value[3] = value[0] * other.value[3] + value[3] * other.value[0] + value[1] * other.value[2] - value[2] * other.value[1];
	return *this;
}

Quaternion operator*(Quaternion const& q1, Quaternion const& q2) {
	Quaternion result(q1);
	result *= q2;
	return result;
}

Quaternion operator+(Quaternion const& q1, Quaternion const& q2) {
	Quaternion result(q1);
	result += q2;
	return result;
}

Quaternion operator-(Quaternion const& q1, Quaternion const& q2) {
	Quaternion result(q1);
	result -= q2;
	return result;
}