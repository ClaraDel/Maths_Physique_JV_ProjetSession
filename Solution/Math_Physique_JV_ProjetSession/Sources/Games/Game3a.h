#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Math/Quaternion.h"
#include "../Physic/ForceGenerator/ParticleForceRegistry.h"

#ifndef DEF_GAME3
#define DEF_GAME3

class Game3a : GameBase {

private:

    ParticleForceRegistry m_registry;
    Vecteur3D velocity;
    Vecteur3D angularVelocity;
    Quaternion orientation;
    float damping;
    float angularDamping;

public:

    Gam3a(std::string nameGame, std::string descriptionGame);

    void doUpdatePhysics() override;
    
    int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;

};
#endif