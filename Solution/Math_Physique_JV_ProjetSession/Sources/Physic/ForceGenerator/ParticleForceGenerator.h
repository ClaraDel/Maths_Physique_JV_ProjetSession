#pragma once

#include "../../Physic/Particule.h"


class ParticleForceGenerator

{
public:
	virtual void UpdateForce(Particule* particle, double duration) = 0;
};

