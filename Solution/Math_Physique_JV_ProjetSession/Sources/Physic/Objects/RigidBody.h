#ifndef DEF_RIGIDBODY
#define DEF_RIGIDBODY
#pragma once
#include <iostream>
#include<vector>
#include "../../Math/Quaternion.h"
#include "../../Math/Matrix34.h"

class RigidBody{

private :

    Vecteur3D m_position ;
    Vecteur3D m_velocity ;
    Vecteur3D m_acceleration;

    double m_inverseMasse;
    double m_damping ;
    double m_angularDamping;

    Quaternion m_orientation ;
    Vecteur3D  m_vit_angular;
    Vecteur3D m_angularAcceleration;

    Matrix34 m_transformMatrix ;
    Matrix33 m_inverseInertiaWorld ;
    Matrix33 m_inverseInertia;

    Vecteur3D m_forceApplied;
    Vecteur3D m_torqueApplied;

public : 
    RigidBody(Vecteur3D pos, Vecteur3D vit, double m, Quaternion orientation, double damping, Vecteur3D angVelocity, double angularDamping, Matrix33 inverseInertia); //a changer!
    ~RigidBody();
    //update position, orientation and velocity
    void integrate(double duration);
    void addForce(Vecteur3D forceToAdd);
    void accelerationCalcul();
    void updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector);
    void updateQuaternion(Vecteur3D const& integrateQuaternion, double deltaTime, Quaternion& quaternion);

    void addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint);
    void addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& LocalPoint);

    double getInverseMasse() const;
    double getMasse() const;
    void setInverseMasse(double value);

    Vecteur3D getPosition();
    Vecteur3D getVelocity();
    Vecteur3D getAcceleration();
    Quaternion getOrientation() ;

    void setPosition(Vecteur3D const& position);

    void setAcceleration(double const x, double const y, double const z);
    void setAngularAcceleration(double const x, double const y, double const z);
    void setVelocity(double const x, double const y, double const z);
    void setAngularVelocity(double const x, double const y, double const z);
    void setVelocity(Vecteur3D v);

    
    void setDamping(double d);

private :
   

    //calculate and normalize the matrix transformation
    void calculateDerivedData();
    void calculateTransformMatrix();
    void calculateTransformInertia();

    void clearAccumulator();
    



};

#endif