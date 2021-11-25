#pragma once

#include "../../../Physic/Objects/RigidBody.h"


class RigidBodyForceGenerator

{
public:
	virtual void UpdateForce(RigidBody* rigidBody, double duration) = 0;
};
