#pragma once

#include "../../Physic/Particule.h"


class ParticleForceGenerator

{
public:
	virtual void UpdateForce(Particule* particle, float duration) = 0;
};

