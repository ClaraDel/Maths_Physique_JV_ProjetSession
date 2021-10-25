#include "Matrix33.h"
Matrix33::Matrix33() {
	for (int i = 0; i < 9; i++) {
		values[i] = 0;
	}
}
Matrix33::Matrix33(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	values[0] = a;
	values[1] = b;
	values[2] = c;
	values[3] = d;
	values[4] = e;
	values[5] = f;
	values[6] = g;
	values[7] = h;
	values[8] = i;
}

double Matrix33::Det() {
	return (values[0] * values[4] * values[8] +
		values[3] * values[7] * values[2] +
		values[6] * values[1] * values[5] -
		values[0] * values[7] * values[5] -
		values[6] * values[4] * values[2] -
		values[3] * values[1] * values[8]);

}
Matrix33 Matrix33::Inverse() {
	if (this->Det() != 0) {
		Matrix33 M;
		M.values[0] = values[4] * values[8] - values[5] * values[7]; //ei-fg
		M.values[1] = values[2] * values[7] - values[1] * values[8]; //ch-bi
		M.values[2] = values[1] * values[5] - values[2] * values[4]; //bf-ce

		M.values[3] = values[5] * values[6] - values[1] * values[8]; // fg-di
		M.values[4] = values[0] * values[8] - values[2] * values[6]; //ai-cg
		M.values[5] = values[2] * values[3] - values[0] * values[5]; // cd -af

		M.values[6] = values[3] * values[7] - values[4] * values[6]; //dh-eg
		M.values[0] = values[1] * values[6] - values[0] * values[7]; //bg-ah
		M.values[0] = values[0] * values[4] - values[2] * values[3]; //ae -bd

		return (1 / (this->Det()) * M);
	}
}
Matrix33 Matrix33::Transpose() {
	// a b c -> a d g
	// d e f -> b e h
	// g h i -> c f i
	Matrix33 M(values[0], values[3], values[6],
		values[1], values[4], values[7],
		values[2], values[5], values[8]);
	return M;
}
void Matrix33::SetOrientation(const Quaternion& q) {}

Matrix33& Matrix33::operator+=(const Matrix33& other) {
	for (int i = 0; i < 9; i++) {
		values[i] += other.values[i];
	}
	return *this;
}
Matrix33& Matrix33::operator-=(const Matrix33& other) {
	for (int i = 0; i < 9; i++) {
		values[i] += other.values[i];

	}
	return *this;
}
Matrix33& Matrix33::operator*=(const Matrix33& other) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				values[i + j] += values[i + k] * other.values[j + k];
			}
		}
	}
	return *this;
}
Matrix33& Matrix33::operator*=(const Vecteur3D& other) {

}
Matrix33& Matrix33:: operator*=(double value) {}


Matrix33 operator*(double value, Matrix33 const& matrix) {

}