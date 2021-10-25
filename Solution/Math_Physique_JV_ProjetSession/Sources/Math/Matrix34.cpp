#include "Matrix34.h"
#include "Matrix33.h"

double Matrix34::Det(){
	Matrix33 M(values[0],values[1],values[2],
				values[4],values[5],values[6],
				values[8],values[9],values[10]);
	return(M.Det());
}

Matrix34 Matrix34::Inverse() {
	Matrix33 M = Matrix33(values[0], values[1], values[2], values[4], values[5], values[6], values[8], values[9], values[10]);
	Matrix33 MInverse = M.Inverse();
	Vecteur3D v = Vecteur3D(values[3], values[7], values[11]);
	Vecteur3D resV = -1 * MInverse * v;
	Matrix34 resM;
	resM.values[0] = MInverse.getValue(0);
	resM.values[1] = MInverse.getValue(1);
	resM.values[2] = MInverse.getValue(2);
	resM.values[4] = MInverse.getValue(3);
	resM.values[5] = MInverse.getValue(4);
	resM.values[6] = MInverse.getValue(5);
	resM.values[8] = MInverse.getValue(6);
	resM.values[9] = MInverse.getValue(7);
	resM.values[10] = MInverse.getValue(8);
	resM.values[3] = MInverse.getValue(resV.getX());
	resM.values[7] = MInverse.getValue(resV.getY());
	resM.values[11] = MInverse.getValue(resV.getZ());
	return resM;
}

void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vecteur3D& p){
	Matrix33 M;
	M.SetOrientation(q);
	values[0] = M.getValue(0);
	values[1] = M.getValue(1);
	values[2] = M.getValue(2);
	values[3] = p.getX();

	values[4] = M.getValue(4);
	values[5] = M.getValue(5);
	values[6] = M.getValue(6);
	values[7] = p.getY();

	values[8] = M.getValue(8);
	values[9] = M.getValue(9);
	values[10] = M.getValue(10);
	values[11] = p.getZ();
}

Vecteur3D Matrix34::localToWorld(const Vecteur3D &local, Matrix34 &transform){
	return transform.TransformPosition(local);
}

Vecteur3D Matrix34::worldToLocal(const Vecteur3D &world, Matrix34 &transform){
	Matrix34 inverse = transform;
	inverse.Inverse();
	return inverse.TransformPosition(world);
}

Vecteur3D Matrix34::TransformPosition(const Vecteur3D& vector){
	return Vecteur3D(
		values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ() + values[3],
		values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ() + values[7],
		values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ() + values[11]);
}

Vecteur3D Matrix34::TransformDirection(const Vecteur3D& vector) {
	return Vecteur3D(
		values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ(),
		values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ(),
		values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ());
}

Matrix34& Matrix34::identity() {
	Matrix34 result;
	result.setValue(0, 1);
	result.setValue(5,1);
	result.setValue(10,1);
	return result;
}


Matrix34& Matrix34::operator+=(const Matrix34& other) {
	for (int i = 0; i < 12; i++) {
		values[i] += other.values[i];
	}
	return *this;
}
Matrix34& Matrix34::operator-=(const Matrix34& other) {
	for (int i = 0; i < 12; i++) {
		values[i] += other.values[i];

	}
	return *this;
}
Matrix34& Matrix34::operator*=(const Matrix34& other) {
	Matrix34 M;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				M.values[i*4 + j] += values[i*4 + k] * other.values[j + 4*k];
			}
		}
	}
	M.values[3] = values[0]*other.values[3] + values[1]*other.values[7]+ values[2]*other.values[11] + values[3];
	M.values[7] = values[4]*other.values[3] + values[5]*other.values[7]+ values[6]*other.values[11] + values[7];
	M.values[11] = values[8] * other.values[3] + values[9] * other.values[7] + values[10] * other.values[11] + values[11];
	*this = M;
	return *this;

}

double Matrix34::getValue(int i) const {
	return values[i];
}

void Matrix34::setValue(int i, double v) {
	values[i] = v ;
}

Matrix34& Matrix34:: operator*=(double value) {
	for (int i = 0;i <12 ; i++){
		values[i]*= value;
	}
	return *this;
}

Matrix34 operator*(Matrix34 const& matrix1, Matrix34 const& matrix2) {
	Matrix34 result(matrix1);
	result *= matrix2;
	return result;
}

Matrix34 operator*(double value, Matrix34 const& matrix) {
		Matrix34 result(matrix);
		result *= value;
		return result;
}

Vecteur3D operator*(Vecteur3D const& vecteur, Matrix34 const& matrix) {
	double result[3];
	double vector[4] = { vecteur.getX(), vecteur.getY(), vecteur.getZ(), 1};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			result[i] += matrix.getValue(i * 4 + j) * vector[j];
		}
	}
	return Vecteur3D(result[0], result[1], result[2]);

}