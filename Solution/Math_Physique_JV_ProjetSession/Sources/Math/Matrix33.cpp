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
	Matrix33 M;
	if (this->Det() != 0) {
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
	return M;
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


void Matrix33::SetOrientation(const Quaternion& q) {
	double w = q.getW();
	double x = q.getX();
	double y = q.getY();
	double z = q.getZ();
	double xy = 2* x * y;
	double zw = 2* z * w;
	double xz = 2* x * z;
	double yw = 2 * y * w;
	double yz = 2 * y * z;
	double xw = 2 * x * w;
	double x2 = 2 * x * x;
	double y2 = 2 * y * y;
	double z2 = 2 * z * z;
	values[0] = 1 - (y2 + z2);
	values[1] = xy + zw;
	values[2] = xz + yw;
	values[3] = xy - zw; 
	values[4] = 1 - (x2 + z2);
	values[5] = yz + xw; 
	values[6] = xz + yw;
	values[7] = yz - xw;
	values[8] = 1 - (x2 + y2);
}


double Matrix33::getValue(int i) const {
	return values[i];
}

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
	Matrix33 M;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				M.values[i*3 + j] += values[3*i + k] * other.values[j + 3*k];
			}
		}
	}
	*this = M;
	return *this;
}



Matrix33& Matrix33:: operator*=(double value) {
	for (int i = 0;i <9 ; i++){
		values[i]*= value;
	}
	return *this;
}

Matrix33 operator*(Matrix33 const& matrix1, Matrix33 const& matrix2) {
	Matrix33 result(matrix1);
	result *= matrix2;
	return result;
}

Matrix33 operator*(double value, Matrix33 const& matrix) {
		Matrix33 result(matrix);
		result *= value;
		return result;
}

Vecteur3D operator*(Matrix33 const& matrix, Vecteur3D const& vecteur) {
	double result[3];
	double vector[3] = { vecteur.getX(), vecteur.getY(), vecteur.getZ() };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i] += matrix.getValue(i * 3 + j) * vector[j];
		}
	}
	return Vecteur3D(result[0], result[1], result[2]);

}