#ifndef DEF_RIGIDBODY
#define DEF_RIGIDBODY
#pragma once
#include<vector>
#include "../Math/Quaternion.h"
#include "../Math/Matrix34.h"

class RigidBody{

private :

    double m_inverseMass;
    double m_damping ;
    Vecteur3D m_position ;
    Vecteur3D m_forceApplied;
    Quaternion m_orientation ;
    Vecteur3D m_velocity ;
    Vecteur3D m_acceleration;
    Vecteur3D m_rotation ;
    Vecteur3D m_angVelocity;
    Matrix34 m_transformMatrix ;
    Matrix33 m_inverseInertiaWorld ;
    double m_angularDamping ;

public : 
    RigidBody(double m = 0.0, Vecteur3D pos = Vecteur3D(), Vecteur3D vit = Vecteur3D(), double f =0); //a changer!
    ~RigidBody();
    //update position, orientation and velocity
    void integrate(float duration);
    void addForce(Vecteur3D forceToAdd);
    

private :
    //calculate and normalize the matrix transformation
    void calculateDerivedData();
    void calculateTransformMatrix(Matrix34& transformMatrix, const Vecteur3D& position, const Quaternion& orientation);
    //void calculateTransformInertia(Matrix33& iitWorld, const Quaternion& q, const Matrix33& iitBody, const Matrix34& rotmat);

};

#endif