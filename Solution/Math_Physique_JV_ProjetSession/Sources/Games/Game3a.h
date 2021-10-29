#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Math/Quaternion.h"
#include "../Physic/ForceGenerator/ParticleForceRegistry.h"
#include "../Physic/RigidBody.h"
#include<vector>
#include "../Physic/Particule.h"

#ifndef DEF_GAME3
#define DEF_GAME3

class Game3a : GameBase {

private:

    //PARTICULE'S ATTRIBUTES
    int rbChosen = 0; //type of projectile chosen
    double ang;
    int shapeOfRb = 1;// 0 -> Sphere, 1-> Cube, 2->Torus, 3-> Teapot,4->ellipse 3D
    Vecteur3D rvbColor; //Particule color 
    Vecteur3D formSize; //vector that contains information about particle's shape 
    std::vector<Particule*> rbTabl;

    ParticleForceRegistry m_registry;
    Vecteur3D velocity;
    Vecteur3D angularVelocity;
    Quaternion orientation;
    float damping;
    float angularDamping;
    


public:

    Game3a(std::string nameGame, std::string descriptionGame);

    void doUpdatePhysics() override;
    void drawParticule(Particule* particule);
    void createRigidBody();
    
    int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;

};
#endif