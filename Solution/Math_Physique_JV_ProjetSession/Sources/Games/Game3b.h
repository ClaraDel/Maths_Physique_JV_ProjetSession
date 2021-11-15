#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Math/Quaternion.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyForceRegistry.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyGravity.h"
#include "../Physic/RigidBody.h"
#include<vector>
#include <cmath>

#ifndef DEF_GAME3B
#define DEF_GAME3B

class Game3b : GameBase {

private:

    //PARTICULE'S ATTRIBUTES
    int rbChosen = 0; //type of projectile chosen
    int shapeOfRb = 1;// 0 -> Sphere, 1-> Cube, 2->Torus, 3-> Teapot,4->ellipse 3D
    Vecteur3D rvbColor; //Rigidbody color 
    Vecteur3D formSize; //vector that contains information about rigidbody's shape 
    std::vector<RigidBody*> rbTabl;

    RigidBodyForceRegistry m_registry;
    bool isLauch;
    int Y;

public:

    Game3b(std::string nameGame, std::string descriptionGame);

    void doUpdatePhysics() override;
    void drawCars(RigidBody* rigidbody);
    void createCars();

    int launch(int argc, char* argv[]) override;
    void doKeyboard(unsigned char key, int x, int y) override;
    void doDisplay() override;

};
#endif