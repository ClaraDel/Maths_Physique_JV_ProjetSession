#pragma once

#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Math/Quaternion.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyForceRegistry.h"
#include "../Physic/ForceGenerator/RigidBody/RigidBodyGravity.h"
#include "../Physic/ForceGenerator/RigidBody/InputForceAtPoint.h"
#include "../Physic/Objects/RigidBody.h"
#include "../Physic/Contact/RigidBodyContact.h"
#include "../Physic/Collision/OcTree.h"
#include "../Physic/Collision/CollisionData.h"
#include "../Physic/Objects/Box.h"
#include "../Physic/Objects/Plane.h"
#include "../Physic/Collision/PossibleCollision.h"
#include<vector>
#include <cmath>

#ifndef DEF_GAME4
#define DEF_GAME4

class Game4 : public GameBase {

private :
	OcTree m_tree;
    bool pause_game;
    //rigidbody
    RigidBody* m_cube;
    Vecteur3D m_rvbColor; //Rigidbody color 
    Vecteur3D m_formSize; //vector that contains information about rigidbody's shape 
    std::vector<Primitive*> m_primitives;
    
    bool isLauch;
    int directionChosen;

    RigidBodyForceRegistry m_registry;
    
    //camera
    int X;
    int Y;
    int Z;


public :
    Game4(std::string nameGame, std::string descriptionGame);

    void doUpdatePhysics() override;
    void drawCube();
    void drawWalls();
    void createCube(Vecteur3D force);
    void createWalls();
    void launchDemo();
    void UpdateOctree();
    void PrintAndStop(CollisionData data);

    int launch(int argc, char* argv[]) override;
    void doKeyboard(unsigned char key, int x, int y) override;
    void doDisplay() override;
};
#endif