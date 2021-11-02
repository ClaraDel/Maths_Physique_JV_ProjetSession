#pragma once
#include <iostream>
#include <string>
#include "GameBase.h"
#include "../Physic/Particule.h"
#include "../Physic/ForceGenerator/ParticleForceGenerator.h"
#include "../Physic/ForceGenerator/ParticleForceRegistry.h"
#include "../Physic/ForceGenerator/ParticleGravity.h"
#include "../Physic/ForceGenerator/ParticleSpring.h"
#include "../Physic/ForceGenerator/ConstantForce.h"
#include"../Physic/Collision/ParticleContactResolver.h"
#include"../Physic/Collision/ParticleContact.h"
#include"../Physic/Collision/ParticleCable.h"
#include"../Physic/Collision/ParticleContactRegistry.h"
#include"../Physic/Collision/ParticleContactGenerator.h"
#include "../Physic/ForceGenerator/ParticleBuoyancy.h"
#ifndef DEF_GAME2
#define DEF_GAME2
#include<vector>

class Game2 : GameBase {

private :
	int Y;
	double m_groundHeight;
	double m_waterHeight;
	int m_nbParticules;
	float particuleSize;
	double m_k;
	double m_l0;
	float m_particuleRestitution ;
	ParticleForceRegistry m_forceRegistry;
	std::vector<ParticleCable*> m_cables;
	ParticleContactRegistry m_contactRegistry;	
	ParticleContactResolver m_resolver;
	std::vector<Particule*> m_blob;

public :
	Game2(std::string nameGame, std::string descriptionGame);

	void createBlob();
	void cleanInput();
	unsigned int createContacts();
	void checkWaterInteractions();
	void checkParticleCollisions();
	void checkGroundCollisions();

	void drawParticule(Particule *particule);
	void launchParticule();
	void doUpdatePhysics() override;
	void doArrows(int key, int xx, int yy) override;

	int launch(int argc, char* argv[]) override;
	void doKeyboard(unsigned char key, int x, int y) override;
	void doDisplay() override;


};

#endif