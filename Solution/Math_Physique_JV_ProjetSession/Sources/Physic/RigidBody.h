#ifndef DEF_RIGIDBODY
#define DEF_RIGIDBODY
#pragma once
#include<vector>
#include "Quaternion.h"
#include "Matrix34.h"

class RigidBody{

private :

    double m_inverseMass
    double m_damping ;
    Vecteur3D m_position ;
    Quaternion orientation ;
    Vecteur3D m_velocity ;
    Vecteur3D m_rotation ;
    Matrix34 transformMatrix ;
    Vecteur3D m_forceApplied

public : 
    RigidBody(double m = 0.0, Vecteur3D pos = Vecteur3D(), Vecteur3D vit = Vecteur3D(), double f =0); //a changer!
    ~RigidBody();
    //update position, orientation and velocity
    void integrate(float duration);
    

private :
    //calculate and normalize the matrix transformation
    void calculateDerivedData();
    void calculateTransformMatrix(Matrix34 &transformMatrix, const Vector &position, const Quaternion &orientation);

};

#endif