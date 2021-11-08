#pragma once

#include "../../../Physic/RigidBody.h"


class RigidBodyForceGenerator

{
public:
	virtual void UpdateForce(RigidBody* rigidBody, double duration) = 0;
};
