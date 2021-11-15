#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Math/Quaternion.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyForceRegistry.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyGravity.h"
#include "../Physic/ForceGenerator/RigidBody/InputForceAtPoint.h"
#include "../Physic/RigidBody.h"
#include<vector>
#include <cmath>

#ifndef DEF_GAME3
#define DEF_GAME3

class Game3a : GameBase {

private:

    //PARTICULE'S ATTRIBUTES
    int rbChosen = 0; //type of projectile chosen
    int shapeOfRb = 1;// 0 -> Sphere, 1-> Cube, 2->Torus, 3-> Teapot,4->ellipse 3D
    Vecteur3D rvbColor; //Rigidbody color 
    Vecteur3D formSize; //vector that contains information about rigidbody's shape 
    std::vector<RigidBody*> rbTabl;

    RigidBodyForceRegistry m_registry;
    bool isLauch;

public:

    Game3a(std::string nameGame, std::string descriptionGame);

    void doUpdatePhysics() override;
    void drawRigidBody(RigidBody* rigidbody);
    void createRigidBody();
    
    int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;

};
#endif