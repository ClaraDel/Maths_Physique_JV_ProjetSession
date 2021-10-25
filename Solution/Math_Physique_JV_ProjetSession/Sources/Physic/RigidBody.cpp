#include "RigidBody.h"

//create transform matrix from position and orientation

RigidBody::RigidBody(double masse, Vecteur3D pos, Vecteur3D vit, double d){ //a changer!

	m_position = pos;
	m_velocity = vit;
	m_acceleration = Vecteur3D();
	m_damping = d;
	m_forceApplied = Vecteur3D();
	
	if(m!=0){
		m_inverseMasse = 1/m;
	} else {
		m_inverseMasse = 0;
	}
}
RigidBody::~RigidBody()
{
}

void RigidBody::calculateTransformMatrix(Matrix34 &transformMatrix, const Vector &position, const Quaternion &orientation) {
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
	transformMatrix.values[0] = 1 - (y2 + z2);
	transformMatrix.values[1] = xy + zw;
	transformMatrix.values[2] = xz + yw;
    transformMatrix.values[3] = position.x
	transformMatrix.values[4] = xy - zw; 
	transformMatrix.values[5] = 1 - (x2 + z2);
	transformMatrix.values[6] = yz + xw;
    transformMatrix.values[7] = position.y
	transformMatrix.values[8] = xz + yw;
	transformMatrix.values[9] = yz - xw;
	transformMatrix.values[10] = 1 - (x2 + y2);
    transformMatrix.values[11] = position.z
}

//calculate the transform Matrix for the RigidBody
void RigidBody::calculateDerivedData(){
    orientation.normalize();
    calculateTransformMatrix(transformMatrix, position, orientation)

}