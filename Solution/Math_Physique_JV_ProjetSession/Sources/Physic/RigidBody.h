#ifndef DEF_RIGIDBODY
#define DEF_RIGIDBODY
#pragma once
#include<vector>
#include "../Math/Quaternion.h"
#include "../Math/Matrix34.h"

class RigidBody{

private :

    double m_inverseMasse;
    double m_damping ;
    double m_angularDamping;
    Vecteur3D m_position ;
    Vecteur3D m_forceApplied;
    Quaternion m_orientation ;
    Vecteur3D m_velocity ;
    Vecteur3D  m_vit_angular;
    Vecteur3D m_acceleration;
    Vecteur3D m_angularAcceleration;
    Vecteur3D m_rotation ;
    Vecteur3D m_angVelocity;
    Vecteur3D m_torqueApplied;
    Matrix34 m_transformMatrix ;
    Matrix33 m_inverseInertiaWorld ;
    Matrix33 m_inverseInertia;

public : 
    RigidBody(Vecteur3D pos, Vecteur3D vit, double m, Quaternion orientation, double damping, Vecteur3D angVelocity, double angularDamping, Matrix33 inverseInertia); //a changer!
    ~RigidBody();
    //update position, orientation and velocity
    void integrate(double duration);
    void addForce(Vecteur3D forceToAdd);
    void accelerationCalcul();
    void updateVector(Vecteur3D const& integrateVector, double deltaTime, Vecteur3D& vector);
    void updateQuaternion(Vecteur3D const& integrateQuaternion, double deltaTime, Quaternion& quaternion);

    double getInverseMasse() const;
    double getMasse() const;
    void setInverseMasse(double value);

    Vecteur3D getPosition();
    Vecteur3D getVelocity();
    Vecteur3D getAcceleration();
    void setPosition(Vecteur3D const& position);
    void setPosition(double const x, double const y, double const z);

    void setAcceleration(double const x, double const y, double const z);
    void setVelocity(double const x, double const y, double const z);
    void setVelocity(Vecteur3D v);

    void setMasse(double value);
    void setDamping(double d);

private :
    void addForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint);
    void addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& LocalPoint);

    //calculate and normalize the matrix transformation
    void calculateDerivedData();
    void calculateTransformMatrix(Matrix34& transformMatrix, const Vecteur3D& position, const Quaternion& orientation);
    void calculateTransformInertia(Matrix33& iitWorld, const Quaternion& q, const Matrix33& iitBody, const Matrix34& rotmat);

    void clearAccumulator();
    



};

#endif